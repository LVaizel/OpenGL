#include "Shader.h"

Shader::Shader()
{
	m_programID = 0;
	m_attrVertices = 0;
	m_attrNormals = 0;
	m_attrTexCoords = 0;
	m_sampler1 = 0;
	m_sampler2 = 0;
	m_result = GL_FALSE;
	m_attrWVP = 0;
	m_infoLogLength = 0;
}

Shader::Shader(const char* _vertexFile, const char* _fragmentFile) : Shader()
{
	LoadShaders(_vertexFile, _fragmentFile);
}

Shader::~Shader(){}

void Shader::Cleanup() {
	glDeleteProgram(m_programID);
}

void Shader::SetFloat(const char* _name, float _val)
{
	GLuint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) 
	{
		glUniform1f(loc, _val);
	}
}

void Shader::SetVec3(const char* _name, glm::vec3 _val)
{
	GLuint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) 
	{
		glUniform3fv(loc, 1, &_val[0]);
	}
}

void Shader::SetMat4(const char* _name, glm::mat4 _val)
{
	GLuint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &_val[0][0]);
	}
}

void Shader::SetTextureSampler(const char* _name, GLuint _texUnit, int _texUnitID, int _val)
{
	GLuint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glActiveTexture(_texUnit);
		glBindTexture(GL_TEXTURE_2D, _val);
		glUniform1i(loc, _texUnitID);
	}
}

void Shader::LoadAttributes()
{
	m_sampler1 = glGetUniformLocation(m_programID, "diffuseTexture");
	m_sampler2 = glGetUniformLocation(m_programID, "specularTexture");
}

void Shader::EvaluateShader(int _infoLength, GLuint _ID)
{
	if(_infoLength > 0)
	{
		vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_ID, _infoLength, NULL, &errorMessage[0]);
		if (errorMessage[0] != '\0') {
			M_ASSERT(0, ("%s\n", &errorMessage[0]));
		}
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type);//Create shader

	//Read shader code from file
	string shaderCode;
	ifstream shaderStream(_filePath, ios::in);
	M_ASSERT(shaderStream.is_open(), ("Failed to open %s.\n", _filePath));
	string line = "";
	while (getline(shaderStream, line))
		shaderCode += "\n" + line;
	shaderStream.close();

	//Compile shader
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	//Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, shaderID);

	//Attach shader to program
	glAttachShader(m_programID, shaderID);

	return shaderID;
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	m_programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
	glLinkProgram(m_programID);

	// Check linking status
	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, m_programID);

	//Free resources
	glDetachShader(m_programID, vertexShaderID);
	glDetachShader(m_programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
}