#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Camera.h"

class Mesh;
class Shader;

class GameController : public Singleton<GameController>
{
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Camera m_camera;
public:
	GameController();
	virtual ~GameController();
	void Initialize();
	void RunGame();
};

#endif // GAMECONTROLLER_H

