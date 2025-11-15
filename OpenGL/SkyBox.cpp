#include "SkyBox.h"
#include "Shader.h"
#include <OBJ_Loader.h>

SkyBox::SkyBox()
{
	m_shader = nullptr;
	m_texture = {};
	m_vertexBuffer = 0;
	m_vertexData = {};
}

SkyBox::~SkyBox()
{
}

void SkyBox::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void SkyBox::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("PV", _pv);
	m_shader->SetTextureSampler("skyboxTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
}

void SkyBox::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//Vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices(), 
		3/*Size*/, 
		GL_FLOAT/*Type*/, 
		GL_FALSE/*Normalize*/, 
		3 * sizeof(float)/*Stride*/, 
		(void*)0/*Offset*/);
}

void SkyBox::Create(Shader* _shader, string _file, std::vector<std::string> _faces)
{
	m_shader = _shader;
	objl::Loader loader;
	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load skybox");

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
		}
	}

	m_texture = Texture();
	m_texture.LoadCubeMap(_faces);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void SkyBox::Render(glm::mat4 _pv)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	
	glUseProgram(m_shader->GetProgramID());
	SetShaderVariables(_pv);
	BindAttributes();
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}