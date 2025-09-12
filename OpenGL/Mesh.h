#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"

class Mesh
{
private:
	GLuint m_vertexBuffer;
	vector<GLfloat> m_vertexData;
public:
	Mesh();
	virtual ~Mesh();
	void Create();
	void Cleanup();
	void Render();
};

#endif // MESH_H

