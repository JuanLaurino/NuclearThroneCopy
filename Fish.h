#pragma once
#include "Character.h"
class Fish :public Character
{
	enum FISH_STATE { ST_IDLE, ST_ONHIT, ST_MOVING, ST_ROLL, ST_FALLEN };

	FISH_STATE _fishState;

	int _lastDirX;
	int _lastDirY;

	int _rotation;
	bool _flip;
	bool _roll;
public:
	Fish();
	~Fish();

	void init();
	void update();
	void render();

	void receiveDamage();
	void receiveDamage(int damage);

	void setState(int state) { _fishState = (FISH_STATE)state; };
};

