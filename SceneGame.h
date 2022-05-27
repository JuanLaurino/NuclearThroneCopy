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
#include "HUD.h"
#include "PickableObject.h"

class SceneGame : public Scene
{
	bool	_changeLevel;
	int		_changeLevelTimer;
	int		_dificultad;

	Level	_nivel;
	Fish	_personaje;
	HUD		_hud;

	std::vector<Chest>				_chest;
	std::vector<Cactus>				_cactus;
	std::vector<GFXElementX*>		_enemies; 
	std::vector<Weapon*>			_weapons;
	std::vector<Bullet*>			_bullets;
	std::vector<PickableObject*>	_pickableObjects;

public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();

	void deletePointers();
};

