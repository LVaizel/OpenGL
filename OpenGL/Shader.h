#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
private:
	GLuint m_programID;
	GLuint m_attrVertices;
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
	GLuint GetAttrVertices() { return m_attrVertices; }

	//Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
};
#endif // SHADER_H

