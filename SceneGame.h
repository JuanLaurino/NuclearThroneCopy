#pragma once
#include "Scene.h"
#include "Level.h"
#include "Fish.h"

class SceneGame : public Scene
{
	Level _nivel;
	Fish _personaje;
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

