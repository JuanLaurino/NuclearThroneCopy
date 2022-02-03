#pragma once
#include "GFXElement.h"
class Background :public GFXElement
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

