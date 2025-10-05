#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
private:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	vector<GLfloat> m_vertexData;
	vector<GLuint> m_indexData;
	glm::mat4 m_world;
	Texture m_texture1;
	Texture m_texture2;
	glm::vec3 m_position;
	glm::vec3 m_rotation;

public:
	Mesh();
	virtual ~Mesh();
	void Create(Shader* _shader);
	void Create(Shader* _shader, GLint _textureWrapperMethod);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	void Render(glm::mat4 _wvp, GLenum _mode);
};

#endif // MESH_H

