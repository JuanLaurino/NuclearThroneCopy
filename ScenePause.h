#pragma once
#include "Scene.h"
class ScenePause : public Scene
{
public:
	ScenePause();
	~ScenePause();

	void init();
	void reinit();
	void update();
	void render();
};

