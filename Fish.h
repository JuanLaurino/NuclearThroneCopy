#pragma once
#include "Character.h"
class Fish :public Character
{
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
};

