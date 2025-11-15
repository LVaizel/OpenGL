#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class SkyBox
{
private:
	Shader* m_shader;
	Texture m_texture;
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;

	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

public:
	//Constructors/Destructors
	SkyBox();
	virtual ~SkyBox();

	//Methods
	void Create(Shader* _shader, string file,std::vector<std::string> _faces);
	void Render(glm::mat4 _pv);
	void Cleanup();
};

#endif // SKYBOX_H
