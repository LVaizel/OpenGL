#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Mesh.h"
#include "Shader.h"
#include "PostProcessor.h"

class GameController : public Singleton<GameController>
{
private:
	vector<Mesh> m_meshBoxes;
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Shader m_shaderPostProcess;
	PostProcessor m_postProcessor;
	SkyBox m_skyBox;
	Camera m_camera;
	GLuint vao;
public:
	GameController();
	virtual ~GameController();
	void Initialize();
	void RunGame();
	void MoveMeshOnMouseClick(Mesh& _mesh);
	void RotateMeshOnMouseClick(Mesh& _mesh);
	void ScaleMeshOnMouseClick(Mesh& _mesh);
};

#endif // GAMECONTROLLER_H

