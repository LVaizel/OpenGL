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
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
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
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 0/*Stride*/, (void*)0/*Offset*/);
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}
