#pragma once
#include "GFXElement.h"
class weapon :public GFXElement
{
	enum WEAPON_STATE { ST_ON_GROUND, ST_EQUIPED, ST_ON_INVENTORY };

	WEAPON_STATE _state;
public:
	weapon();
	~weapon();

	void update();
	void render();
};

