#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexData = { };
	m_texture = { };
	m_shader = nullptr;
	m_world = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	//m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg");

	m_vertexData = {
		/* Position */ /* RGBA Color */ /* Texture Coords */
		50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
		50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top-left
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(double), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Create(Shader* _shader, GLint _textureWrapperMethod)
{
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg", _textureWrapperMethod);

	m_vertexData = {
		/* Position */ /* Color */      /* Texture Coords */
		50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f,  // top-right
		50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, // bottom-right  
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, // bottom-left
		-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 2.0f,  // top-left
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(double), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), 2/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 8 * sizeof(float)/*Stride*/, (void*)(6 * sizeof(float))/*Offset*/);

	m_rotation.y += 0.0001f;
	glm::mat4 transform = glm::rotate(_wvp, m_rotation.y, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexData.size()), GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
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
