#pragma once
#include "Scene.h"
class SceneGameOver : public Scene
{
public:
	SceneGameOver();
	~SceneGameOver();

	void init();
	void reinit();
	void update();
	void render();
};

