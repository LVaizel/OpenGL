#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexData = { };
	m_shader = nullptr;
	m_world = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));
	//m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;
	//Icosahedron data
	float a = 20.0f;
	float b = 42.0f;
	m_vertexData = {
		/* Position, Color */
		-a, 0.0f, b, 1.0f, 0.0f, 0.0f, 1.0f, // Red
		a, 0.0f, b, 1.0f, 0.549f, 0.0f, 1.0f, // Orange
		-a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f, // Yellow
		a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f, // Green
		0.0f, b, a, 0.0f, 0.0f, 1.0f, 1.0f, // Blue
		0.0f, b, -a, 0.294f, 0.0f, 0.51f, 1.0f, // Indigo
		0.0f, -b, a, 0.502f, 0.0f, 0.502f, 1.0f, // Purple
		0.0f, -b, -a, 1.0f, 1.0f, 1.0f, 1.0f, // White
		b, a, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Cyan
		-b, a, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Black
		b, -a, 0.0f, 0.118f, 0.565f, 1.0f, 1.0f, // Dodge-Blue
		-b, -a, 0.0f, 0.863f, 0.078f, 0.235f, 1.0f // Crimson
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
		1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
		3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
		5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
		7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLuint), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), 4/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);

	m_world = glm::rotate(m_world, 0.0001f, glm::vec3(0, 1, 0));
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexData.size()), GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrColors());
}

void Mesh::Render(glm::mat4 _wvp, GLenum _mode)
{
	
	_wvp *= m_world;

	glUseProgram(m_shader->GetProgramID());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), 4/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);

	glDrawArrays(_mode, 0, m_vertexData.size() / 7);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}
