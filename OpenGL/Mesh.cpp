#include "Mesh.h"
#include "Shader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexData = { };
	m_texture1 = { };
	m_texture2 = { };
	
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

	m_texture1 = Texture();
	m_texture1.LoadTexture("../Assets/Textures/MetalFrameWood.jpg");

	m_texture2 = Texture();
	m_texture2.LoadTexture("../Assets/Textures/MetalFrame.jpg");

	m_vertexData = {
		/* Position */       /* Normals */     /* Texture Coords */
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f

	};

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

	m_shader->SetFloat("material.specularStrength", 8.0f);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture1.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());

	/*m_shader->SetVec3("light[0].ambientColor", glm::vec3(0.4f, 0.4f, 0.4f));
	m_shader->SetVec3("light[0].diffuseColor", Lights[0].GetColor());
	m_shader->SetVec3("light[0].specularColor", { 3, 3, 3 });

	m_shader->SetFloat("light[0].constant", 1.0f);
	m_shader->SetFloat("light[0].linear", 0.09f);
	m_shader->SetFloat("light[0].quadratic", 0.032f);

	m_shader->SetVec3("light[0].position", Lights[0].GetPosition());
	m_shader->SetVec3("light[0].direction", glm::vec3(0.0f, 0.0f, 0.0f) - Lights[0].GetPosition());
	m_shader->SetFloat("light[0].coneAngle", glm::radians(5.0f));
	m_shader->SetFloat("light[0].fallOff", 200);*/

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
		m_shader->SetFloat(Concat("light[",i,"].fallOff").c_str(), 200);
	}
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
	m_texture1.Cleanup();
	m_texture2.Cleanup();
}