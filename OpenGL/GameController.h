#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

class GameController : public Singleton<GameController>
{
private:
	Mesh m_meshBox;
	Mesh m_meshLight;
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Camera m_camera;
public:
	GameController();
	virtual ~GameController();
	void Initialize();
	void RunGame();
};

#endif // GAMECONTROLLER_H

