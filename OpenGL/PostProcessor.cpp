#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

PostProcessor::PostProcessor()
{
	m_frameBuffer = 0;
	m_textureColorBuffer = 0;
	m_renderBufferObject = 0;
	m_vertexBuffer = 0;
	m_postProcessingShader = nullptr;

}

PostProcessor::~PostProcessor()
{
}

void PostProcessor::Createvertices()
{
	float vertexData[] = {
		// Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::CreateBuffers()
{
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	glGenTextures(1, &m_textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	Resolution r = WindowController::GetInstance().GetResolution();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);

	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.m_width, r.m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);

	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableVertexAttribArray(m_postProcessingShader->GetAttrVertices());
	glVertexAttribPointer(m_postProcessingShader->GetAttrVertices(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(m_postProcessingShader->GetAttrTexCoords());
	glVertexAttribPointer(m_postProcessingShader->GetAttrTexCoords(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void PostProcessor::Create(Shader* _postProcessingShader)
{
	m_postProcessingShader = _postProcessingShader;
	CreateBuffers();
	Createvertices();
}

void PostProcessor::Cleanup()
{
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteTextures(1, &m_textureColorBuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_postProcessingShader->GetProgramID());
	m_postProcessingShader->SetTextureSampler("screenTexture", GL_TEXTURE0, 0, m_textureColorBuffer);
	BindVertices();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(m_postProcessingShader->GetAttrVertices());
	glDisableVertexAttribArray(m_postProcessingShader->GetAttrTexCoords());
}
