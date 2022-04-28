#pragma once
#include "GFXElementX.h"
#include "Level.h"
#include "weapon.h"
#include "Chest.h"
#include "Maggot.h"
#include <iostream>
#include <vector>

#define MovementSpeed 3

class Character :public GFXElementX
{
protected:
	enum PLAYER_STATE { ST_IDLE, ST_ONHIT, ST_MOVING, ST_FALLEN };

	PLAYER_STATE _state;
	notSDL_Rect _rectFrame;

	bool _canMove;
	int _HP;
	int _MaxHP;
	int _contador;
	int _contadorAnim;
	int _frame;

	Weapon* _inventory[2];
	Level* _pLevel;
	std::vector<Chest>* _chest;
	Maggot* _maggots[20];
public:
	Character();
	~Character();

	void checkForItem();
	void checkCollision(int direction);
	void setWorldPointer(Level* nivel) ;
	void setChestPointer(std::vector<Chest>* chest); //Cambiar por vector
	void setMaggotPointer(Maggot* maggots[20]);//Cambiar por vector "virtual"
	void setWeapon00(Weapon* wp) {_inventory[0] = wp; };
	void setWeapon01(Weapon* wp) { _inventory[1] = wp; };
};

