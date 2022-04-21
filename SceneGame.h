#pragma once
#include "Scene.h"
#include "Level.h"
#include "Fish.h"
#include "Weapon.h"
#include <iostream>
#include <vector>
#include "Maggot.h"
#include "Chest.h"

class SceneGame : public Scene
{
	Level _nivel;
	Fish _personaje;

	std::vector<Maggot> _maggots;
	Weapon _weapons[3]; // máximo 3 por nivel (el jugador puede guardar hasta 2 y puede salir hasta 1 por nivel nuevo)

	Chest _chest[4];

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

