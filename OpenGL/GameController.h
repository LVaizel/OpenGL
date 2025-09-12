#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"

class Mesh;

class GameController : public Singleton<GameController>
{
private:
	Mesh* m_mesh;

public:
	GameController();
	virtual ~GameController();
	void Initialize();
	void RunGame();
};

#endif // GAMECONTROLLER_H

