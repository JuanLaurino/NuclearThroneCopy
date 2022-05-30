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
	enum PLAYER_STATE { ST_IDLE, ST_ONHIT, ST_MOVING, ST_ROLL, ST_FALLEN };

	PLAYER_STATE _state;
	notSDL_Rect _rectFrame;

	bool _canMove;
	bool _canReceiveDamage;
	bool _immune;

	int _MaxHP;
	int _ammo[5];
	int _maxAmmo[5];

	int _contador;
	int _contadorRDaño;
	int _contadorAnim;
	int _frame;
	int _shootBlocked;
	int _amountShoot;
	int _actionCD;
	int _shootCD;
	int _currentShootCD;

	Weapon* _inventory[2];

	std::vector<Weapon*>*			 _weapons;
	std::vector<Chest>*				 _chest;
	std::vector<GFXElementX*>		*_enemies;
public:
	Character();
	~Character();

	virtual void init()		{ };
	virtual void update()	{ };
	virtual void render()	{ };

	virtual void receiveDamage();
	virtual void receiveDamage(int damage)	{  };
	virtual void setState(int state) { _state = (PLAYER_STATE)state; };

	void checkForItem();
	void shoot();
	void swapWeapon();

	int getHP() { return _HP; };
	int getMaxHP() { return _MaxHP; };
	int getAmmo(int i) { return _ammo[i]; };
	Weapon* getInventoryWeapon0() { return _inventory[0]; };
	Weapon* getInventoryWeapon1() { return _inventory[1]; };

	void pickUpWeapon(Weapon* wp);
	void addHP(short amount);
	void addAmmo(short type);

	void setWeaponPointer(std::vector<Weapon*> *weapons) { _weapons = weapons; };
	void setChestPointer(std::vector<Chest>* chest) { _chest = chest; };
	void setEnemiesPointer(std::vector<GFXElementX*>* enemies) { _enemies = enemies; };
	void setImmunity(bool immune) { _immune = immune; };

	void setWeapon00(Weapon* wp) { _inventory[0] = wp; wp->setState(2); };
	void setWeapon01(Weapon* wp) { _inventory[1] = wp; wp->setState(1); };
};