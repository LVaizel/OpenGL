#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
private:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	vector<GLfloat> m_vertexData;
public:
	Mesh();
	virtual ~Mesh();
	void Create(Shader* _shader);
	void Cleanup();
	void Render();
};

#endif // MESH_H

