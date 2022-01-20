#pragma once
#include "Scene.h"
class SceneStats : public Scene
{
public:
	SceneStats();
	~SceneStats();

	void init();
	void reinit();
	void update();
	void render();
};

