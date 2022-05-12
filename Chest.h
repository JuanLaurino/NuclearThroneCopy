#pragma once
#include "GFXElementX.h"
#include "weapon.h"

class Chest : public GFXElementX
{
	enum CHEST_STATE { ST_IDLE, ST_ANIM, ST_OPENING, ST_OPEN };

	CHEST_STATE _chestState;
	short _type;
	int _wait;

	int _contador;
	int _contadorAnim;
	int _frame;

	std::vector<Weapon*>* _weapons;
public:
	Chest();
	~Chest();

	void init(int _type);
	void update();
	void render();

	void setWeaponPointer(std::vector<Weapon*>* weapons) { _weapons = weapons; }
	void open();
	bool isOpen();
	short getType() { return _type; };
};

