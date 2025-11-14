#include "Mesh.h"
#include "Shader.h"

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
	m_lightPosition = { 0, 0, 0 };
	m_lightColor = { 1, 1, 1 };
	m_cameraPosition = { 0, 0, 0 };
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
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

	//m_indexData = {
	//	2, 0, 3, 2, 1, 0
	//};

	//glGenBuffers(1, &m_indexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(double), m_indexData.data(), GL_STATIC_DRAW);
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

	m_shader->SetVec3("light.position", m_lightPosition);
	m_shader->SetVec3("light.color", m_lightColor);
	m_shader->SetVec3("light.ambientColor", glm::vec3(0.1f, 0.1f, 0.1f));
	m_shader->SetVec3("light.diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader->SetVec3("light.specularColor", { 3, 3, 3 });
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

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
void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	//m_rotation.y += 0.001f;

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	//glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexData.size()), GL_UNSIGNED_INT, (void*)0);
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

//void Mesh::Create(Shader* _shader, int mode)
//{
//	m_shader = _shader;
//
//	switch (mode) 
//	{
//	case 1:
//		m_texture1 = Texture();
//		m_texture1.LoadTexture("../Assets/Textures/Wood.jpg");
//		m_texture2.Cleanup();
//		m_texture2 = { };
//
//		m_vertexData = {
//			/* Position */ /* RGBA Color */ /* Texture Coords */
//			50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
//			50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//			-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//			-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top-left
//		};
//
//		break;
//	case 2:
//		m_texture1 = Texture();
//		m_texture1.LoadTexture("../Assets/Textures/Wood.jpg");
//
//		m_texture2 = Texture();
//		m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");
//
//		m_vertexData = {
//			/* Position */ /* RGBA Color */ /* Texture Coords */
//			50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top-right
//			50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom-right
//			-50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//			-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top-left
//		};
//
//		break;
//	case 3:
//		m_texture1 = Texture();
//		m_texture1.LoadTexture("../Assets/Textures/Wood.jpg");
//
//		m_texture2 = Texture();
//		m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");
//
//		m_vertexData = {
//			/* Position */ /* RGBA Color */ /* Texture Coords */
//			50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
//			50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//			-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//			-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top-left
//		};
//		break;
//	}
//	
//	glGenBuffers(1, &m_vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
//
//	m_indexData = {
//		2, 0, 3, 2, 1, 0
//	};
//
//	glGenBuffers(1, &m_indexBuffer);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(double), m_indexData.data(), GL_STATIC_DRAW);
//}


//void Mesh::Render(glm::mat4 _wvp, GLenum _mode)
//{
//	
//	_wvp *= m_world;
//
//	glUseProgram(m_shader->GetProgramID());
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
//
//	glEnableVertexAttribArray(m_shader->GetAttrVertices());
//	glVertexAttribPointer(m_shader->GetAttrVertices(), 3/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)0/*Offset*/);
//
//	glEnableVertexAttribArray(m_shader->GetAttrNormals());
//	glVertexAttribPointer(m_shader->GetAttrNormals(), 4/*Size*/, GL_FLOAT/*Type*/, GL_FALSE/*Normalize*/, 7 * sizeof(float)/*Stride*/, (void*)(3 * sizeof(float))/*Offset*/);
//	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
//
//	glDrawArrays(_mode, 0, m_vertexData.size() / 7);
//	glDisableVertexAttribArray(m_shader->GetAttrVertices());
//}
