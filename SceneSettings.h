#pragma once
#include "Scene.h"
class SceneSettings : public Scene
{
public:
	SceneSettings();
	~SceneSettings();

	void init();
	void reinit();
	void update();
	void render();
};

