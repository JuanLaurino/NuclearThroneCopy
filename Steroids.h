#pragma once
#include "Character.h"
class Steroids : public Character
{
	int _lastDirX;
	int _lastDirY;

	int _rotation;
	bool _flip;
	bool _roll;
public:
	Steroids();
	~Steroids();

	void init();
	void update();
	void render();

	void receiveDamage();
	void receiveDamage(int damage);
};