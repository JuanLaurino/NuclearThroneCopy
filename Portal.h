#pragma once
#include "GFXElementX.h"
class Portal :public GFXElementX
{
	int _contadorAnim;
	int _frame;
public:
	Portal();
	~Portal();

	void init();
	void update();
	void render();
};

