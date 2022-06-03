#pragma once
#include "Scene.h"
#include "Level.h"
#include "Character.h"
#include "Weapon.h"
#include <iostream>
#include <vector>
#include "Maggot.h"
#include <vector>
#include "Chest.h"
#include "Cactus.h"
#include "Bullet.h"
#include "HUD.h"
#include "Portal.h"

class SceneGame : public Scene
{
	bool		_changeLevel;
	int			_changeLevelTimer;
	int			_dificultad;

	bool		_justSpawned;
	bool		_takeSS;
	bool		_doOnce;
	int			_timer;

	Level		_nivel;
	Character*	_personaje;
	HUD			_hud;
	Portal		_portal;

	std::vector<Chest>				_chest;
	std::vector<Cactus>				_cactus;
	std::vector<GFXElementX*>		_enemies; 
	std::vector<Weapon*>			_weapons;
	std::vector<Bullet*>			_bullets;
	std::vector<GFXElement*>		_pickableObjects;

public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();

	void spawnActorsInMap();
	void deletePointers();
	void reset();
};

