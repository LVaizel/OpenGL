#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
private:
	//Members
	Shader* m_shader;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	Texture m_texture1;
	Texture m_texture2;
	vector<GLfloat> m_vertexData;
	vector<GLuint> m_indexData;

	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;

	//Lights
	glm::vec3 m_cameraPosition;
	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;

	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
public:
	//Constructors/Destructors
	Mesh();
	virtual ~Mesh();

	//Getter/Setters
	void SetRotation(glm::vec3 _rotation) { m_rotation = _rotation; }
	glm::vec3 GetRotation() { return m_rotation; }
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetLightPosition(glm::vec3 _lightPos) { m_lightPosition = _lightPos; }
	void SetLightColor(glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetCameraPosition(glm::vec3 _cameraPos) { m_cameraPosition = _cameraPos; }

	//Methods
	void Create(Shader* _shader);
	void CalculateTransform();
	void Render(glm::mat4 _pv);
	void Cleanup();
	//void Create(Shader* _shader, GLint _textureWrapperMethod);
	//void Render(glm::mat4 _wvp, GLenum _mode);
};

#endif // MESH_H

