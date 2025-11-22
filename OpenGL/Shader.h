#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
private:
	GLuint m_programID;
	GLuint m_attrNormals;
	GLuint m_attrVertices;
	GLuint m_attrTexCoords;
	GLuint m_sampler1;
	GLuint m_sampler2;
	GLuint m_attrWVP;

	GLint m_result = GL_FALSE;
	int m_infoLogLength;
	
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _ID);
public:
	//Constructors
	Shader();
	Shader(const char* _vertexFilePath, const char* _fragmentFilePath);
	virtual ~Shader();

	//Accessors
	GLuint GetProgramID() { return m_programID; }
	GLuint GetAttrNormals() { return m_attrNormals; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrTexCoords() { return m_attrTexCoords; }
	GLuint GetSampler1() { return m_sampler1; }
	GLuint GetSampler2() { return m_sampler2; }
	GLuint GetAttrWVP() { return m_attrWVP; }

	//Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetFloat(const char* _name, float _val);
	void SetVec3(const char* _name, glm::vec3 _val);
	void SetMat4(const char* _name, glm::mat4 _val);
	void SetTextureSampler(const char* _name, GLuint _texUnit, int _texUnitID, int _val);
	void SetInt(const char* _name, int _val);
};
#endif // SHADER_H

