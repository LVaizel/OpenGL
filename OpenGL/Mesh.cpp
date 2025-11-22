#include "Mesh.h"
#include "Shader.h"
#include <OBJ_Loader.h>
vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexData = { };
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_enableNormalMap = false;
	
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_world = glm::mat4(1.0f);
	m_scale = { 1, 1, 1 };
	m_cameraPosition = { 0, 0, 0 };
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader, string _file)
{
	m_shader = _shader;

#pragma region LoadMesh
	objl::Loader loader;

	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh");

	for(unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];
		for(unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
		}
	}
#pragma endregion

#pragma region LoadTextures
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));

	m_textureSpecular = Texture();
	if(loader.LoadedMaterials[0].map_Ks != "")
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
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}
void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);

	for(unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetVec3(Concat("light[",i,"].color").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[",i,"].ambientColor").c_str(), glm::vec3(0.1f, 0.1f, 0.1f));
		m_shader->SetVec3(Concat("light[",i,"].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[",i,"].specularColor").c_str(), { 3, 3, 3 });

		m_shader->SetFloat(Concat("light[",i,"].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[",i,"].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[",i,"].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[",i,"].direction").c_str(), glm::normalize(glm::vec3(0.0f + i * 0.1f, 0.0f, 0.0f + i * 0.1f) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[",i,"].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[",i,"].fallOff").c_str(), 200.0f);
	}

	m_shader->SetFloat("material.specularStrength", 8.0f);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
	
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	//Vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);

	//Normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);

	//TexCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), 2/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)(6 * sizeof(float))/*Offset*/);
}
string Mesh::Concat(string s1, int index, string s2)
{
	return s1 + to_string(index) + s2;
}
string Mesh::RemoveFolder(string _fullPath)
{
	const size_t last_slash_idx = _fullPath.find_last_of("\\");
	if(std::string::npos != last_slash_idx)
	{
		_fullPath.erase(0, last_slash_idx + 1);
	}

	return _fullPath;
}
void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	//m_rotation.y += 0.001f;

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 8);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}