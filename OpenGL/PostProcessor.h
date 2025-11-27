#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
private:
	GLuint m_frameBuffer;
	GLuint m_textureColorBuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer;
	Shader* m_postProcessingShader;

	void Createvertices();
	void CreateBuffers();
	void BindVertices();
public:
	PostProcessor();
	virtual ~PostProcessor();
	void Create(Shader* _postProcessingShader);
	void Cleanup();
	void Start();
	void End();
};

