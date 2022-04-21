#pragma once
#include "GFXElement.h"
class Bullet : public GFXElement
{
	int direction;
public:
	Bullet();
	~Bullet();

	void init(int direction);
	void update();
};

