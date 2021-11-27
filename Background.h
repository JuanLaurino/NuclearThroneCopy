#pragma once
#include "ElementoGFX.h"
class Background :public ElementoGFX
{
	int _contador;
	int _frame;
	int _bSpriteID[97];
public:
	Background();
	~Background();

	void init();
	void update();
};

