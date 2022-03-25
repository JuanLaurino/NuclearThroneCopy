#pragma once
#include "GFXElement.h"

enum WEAPON_STATE { ST_ON_GROUND, ST_EQUIPED, ST_ON_INVENTORY };

class Weapon :public GFXElement
{
	WEAPON_STATE _state;
	int _weaponType;
public:
	Weapon();
	~Weapon();

	void init();
	void update();
	void render();
	void renderInventory(int posX, int posY, double angulo);
	void setState(WEAPON_STATE ws) { _state = ws; };
};

