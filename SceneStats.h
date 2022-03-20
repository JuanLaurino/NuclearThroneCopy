#pragma once
#include "Scene.h"
#include "Highscore.h"

class SceneStats : public Scene
{
	Highscore _highscore;
public:
	SceneStats();
	~SceneStats();

	void init();
	void reinit();
	void update();
	void render();
};

