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

class SceneGame : public Scene
{
	Level _nivel;
	Fish _personaje;

	//std::vector<Maggot> _maggots; // error
	Maggot _maggots[20];
	Weapon _weapons[3]; // m�ximo 3 por nivel (el jugador puede guardar hasta 2 y puede salir hasta 1 por nivel nuevo)

	std::vector<Chest> _chest; // VOY POR AQUI SEGUIRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

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

