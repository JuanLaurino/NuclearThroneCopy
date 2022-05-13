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

	int _radLevel;
	int _radExp;

	bool _canMove;
	int _MaxHP;
	int _contador;
	int _contadorAnim;
	int _frame;

	int _shootCD;
	int _currentShootCD;
	int _ammo[5];
	int _maxAmmo[5];
	Weapon* _inventory[2];

	std::vector<Weapon*>* _weapons;
	std::vector<Chest>* _chest;
	std::vector<GFXElementX*> *_enemies;
public:
	Character();
	~Character();

	void checkForItem();
	void receiveDamage();
	void shoot();

	void dropWeapon(); // Deprecated Xd 
	void pickUpWeapon(Weapon* wp);
	void addHP(short amount);
	void addAmmo(short type);

	void setWeaponPointer(std::vector<Weapon*> *weapons) { _weapons = weapons; };
	void setChestPointer(std::vector<Chest>* chest) { _chest = chest; };
	void setEnemiesPointer(std::vector<GFXElementX*>* enemies) { _enemies = enemies; };
	void setWeapon00(Weapon* wp) { _inventory[0] = wp; wp->setState(2); };
	void setWeapon01(Weapon* wp) { _inventory[1] = wp; wp->setState(1); };

	int getRadLevel() { return _radLevel; };
	int getRadExp() { return _radExp; };
};

