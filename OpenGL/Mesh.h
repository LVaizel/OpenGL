#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include <OBJ_Loader.h>
class Shader;

class Mesh
{
private:
	//Members
	Shader* m_shader;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	GLuint m_instanceBuffer;

	Texture m_textureDiffuse;
	Texture m_textureSpecular;
	Texture m_textureNormal;
	
	vector<GLfloat> m_vertexData;
	vector<GLuint> m_indexData;
	vector<GLfloat> m_instanceData;
	bool m_enableNormalMap;

	int m_instanceCount;
	bool m_enableInstancing;
	int m_elementSize;

	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;
	glm::vec3 m_color;
	glm::vec3 m_cameraPosition;

	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string s1, int index, string s2);
	string RemoveFolder(string _fullPath);
	void CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);
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
	void SetCameraPosition(glm::vec3 _cameraPos) { m_cameraPosition = _cameraPos; }

	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }

	//Methods
	void Create(Shader* _shader, string _file, int _instanceCount = 1);
	void CalculateTransform();
	void Render(glm::mat4 _pv);
	void Cleanup();

	//Members
	static vector<Mesh> Lights;
};

#endif // MESH_H

