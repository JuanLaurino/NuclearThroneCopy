#pragma once
#include "GFXElementX.h"
class Chest : public GFXElementX
{
public:
	Chest();
	~Chest();

	void init(int sprite, int prueba);
	void render();
};

