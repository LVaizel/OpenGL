#include "Mesh.h"
#include "Shader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;

	m_vertexData = { };
	m_indexData = { };
	m_instanceData = { };
	m_instanceCount = 1;

	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };

	m_enableNormalMap = false;
	m_enableInstancing = false;

	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_world = glm::mat4(1.0f);
	m_scale = { 1, 1, 1 };
	m_cameraPosition = { 0, 0, 0 };

	m_specularColor = { 2, 3, 3 };
	m_specularStrength = 4.0f;
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader, string _file, int _instanceCount)
{
	m_shader = _shader;
	m_instanceCount = _instanceCount;
	if (m_instanceCount > 1) {
		m_enableInstancing = true;
	}
	else {
		m_enableInstancing = false;
	}
#pragma region LoadMesh
	objl::Loader loader;

	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh");

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];
		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangle;

		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		for (unsigned int j = 0; j < curMesh.Indices.size(); j += 3)
		{
			triangle.clear();
			triangle.push_back(curMesh.Vertices[curMesh.Indices[j]]);
			triangle.push_back(curMesh.Vertices[curMesh.Indices[j + 1]]);
			triangle.push_back(curMesh.Vertices[curMesh.Indices[j + 2]]);

			CalculateTangents(triangle, tangent, bitangent);

			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

			if (loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}
#pragma endregion

#pragma region LoadTextures
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));

	m_textureSpecular = Texture();
	if (loader.LoadedMaterials[0].map_Ks != "")
	{
		m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
	}

	m_textureNormal = Texture();
	if (loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;
	}
#pragma endregion
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime());
		for (unsigned int i = 0; i < m_instanceCount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.2 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20));
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m_instanceData.push_back(model[x][y]);
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, m_instanceData.size() * sizeof(float), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, m_rotation.z, glm::vec3(0, 0, 1));
	m_world = glm::scale(m_world, m_scale);
}
void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetVec3(Concat("light[", i, "].color").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), glm::vec3(0.2f, 0.2f, 0.2f));
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), Lights[i].GetSpecularColor());

		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3(0.0f + i * 0.1f, 0.0f, 0.0f + i * 0.1f) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].fallOff").c_str(), 200.0f);
	}

	m_shader->SetFloat("material.specularStrength", m_specularStrength);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());

}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	int stride = 8;
	if (m_enableNormalMap)
	{
		stride += 6;
	}

	stride *= sizeof(float);
#pragma region BindVertexData
	//Vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, stride, (void*)0/*Offset*/);

	//Normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, stride, (void*)(3 * sizeof(float))/*Offset*/);

	//TexCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), 2/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, stride, (void*)(6 * sizeof(float))/*Offset*/);

	m_elementSize = 8;
#pragma endregion
#pragma region BindNormalData
	if (m_enableNormalMap)
	{
		// Tangent (3 floats, Offset 8*sizeof(float))
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(), 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));

		// Bitangent (3 floats, Offset 11*sizeof(float))
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(), 3, GL_FLOAT, GL_FALSE, stride, (void*)(11 * sizeof(float)));

		m_elementSize += 6;
	}
#pragma endregion
#pragma region BindInstanceData
	if (m_enableInstancing)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
		for (int i = 0; i < 4; i++)
		{
			glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + i);
			glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
			glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + i, 1);
		}
	}
#pragma endregion
}
string Mesh::Concat(string s1, int index, string s2)
{
	return s1 + to_string(index) + s2;
}
string Mesh::RemoveFolder(string _fullPath)
{
	const size_t last_slash_idx = _fullPath.find_last_of("\\");
	if (std::string::npos != last_slash_idx)
	{
		_fullPath.erase(0, last_slash_idx + 1);
	}

	return _fullPath;
}
void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;

	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}
void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	//m_rotation.y += 0.001f;

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	if (m_enableInstancing)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize, m_instanceCount);
	}
	else 
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize);
	}
	
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
	if(m_enableNormalMap)
	{
		glDisableVertexAttribArray(m_shader->GetAttrTangents());
		glDisableVertexAttribArray(m_shader->GetAttrBitangents());
	}
	if(m_enableInstancing)
	{
		for (int i = 0; i < 4; i++)
		{
			glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + i);
		}
	}
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}