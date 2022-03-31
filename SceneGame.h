#pragma once
#include "Scene.h"
#include "Level.h"
#include "Fish.h"
#include "Weapon.h"

class SceneGame : public Scene
{
	Level _nivel;
	Fish _personaje;

	// Prueba
	Weapon arma01;
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

