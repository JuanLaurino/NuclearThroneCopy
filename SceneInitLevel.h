#pragma once
#include "Scene.h"
class SceneInitLevel : public Scene
{
public:
	SceneInitLevel();
	~SceneInitLevel();

	void init();
	void reinit();
	void update();
	void render();
};

