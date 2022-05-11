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

	Weapon _weapons[3]; // máximo 3 por nivel (el jugador puede guardar hasta 2 y puede salir hasta 1 por nivel nuevo)

	std::vector<Chest> _chest;
	std::vector<GFXElementX*> _enemies; 
	std::vector<Cactus> _cactus;
	std::vector<Bullet*> _bullets;

	// Prueba
	Weapon arma01;
	Weapon arma02;
public:
	SceneGame();
	~SceneGame();

	void init();
	void reinit();
	void update();
	void render();
};

