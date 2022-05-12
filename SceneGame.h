#pragma once
#include "Scene.h"
#include "Level.h"
#include "Fish.h"
#include "Weapon.h"
#include <iostream>
#include <vector>
#include "Maggot.h"
#include <vector>
#include "Chest.h"
#include "Cactus.h"
#include "Bullet.h"

class SceneGame : public Scene
{
	Level _nivel;
	Fish _personaje;

	std::vector<Chest> _chest;
	std::vector<Cactus> _cactus;
	std::vector<GFXElementX*> _enemies; 
	std::vector<Weapon*> _weapons;
	std::vector<Bullet*> _bullets;
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

