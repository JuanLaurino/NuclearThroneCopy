#pragma once
#include "Scene.h"
#include "Level.h"
#include "Character.h"
class SceneGame : public Scene
{
	Level _nivel;
	Character _personaje;
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

