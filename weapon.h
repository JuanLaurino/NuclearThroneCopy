#pragma once
#include "GFXElementX.h"

enum WEAPON_STATE { ST_ON_GROUND, ST_ON_INVENTORY, ST_EQUIPED};

class Weapon :public GFXElementX
{
	WEAPON_STATE _state;
	int _weaponType;
	int rotation;
public:
	Weapon();
	~Weapon();

	void init(int weaponType);
	void update();
	void render();
	void renderInventory(int posX, int posY, double angulo, int rotated);

	int getState() { return _state; };
	int getType() { return _weaponType; };
	void setState(int ws) { _state = (WEAPON_STATE)ws; };
};

