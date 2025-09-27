#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
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

public:
	Mesh();
	virtual ~Mesh();
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	void Render(glm::mat4 _wvp, GLenum _mode);
};

#endif // MESH_H

