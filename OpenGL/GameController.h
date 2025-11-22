#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Mesh.h"
#include "Shader.h"

class GameController : public Singleton<GameController>
{
private:
	vector<Mesh> m_meshBoxes;
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	SkyBox m_skyBox;
	Camera m_camera;
	GLuint vao;
public:
	GameController();
	virtual ~GameController();
	void Initialize();
	void RunGame();
};

#endif // GAMECONTROLLER_H

