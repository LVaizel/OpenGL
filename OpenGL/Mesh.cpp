#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_vertexBuffer = 0;
	m_vertexData = { };
	m_shader = nullptr;
	m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;
	m_vertexData = {
		0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	};
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(GLfloat), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp)
{
	_wvp *= m_world;

	glUseProgram(m_shader->GetProgramID());

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), 4/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size()/7);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}
