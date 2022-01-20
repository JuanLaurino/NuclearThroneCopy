#pragma once
#include "Scene.h"
class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

