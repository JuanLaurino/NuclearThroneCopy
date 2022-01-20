#pragma once
#include "ElementoGFX.h"
class ThroneLogo :public ElementoGFX
{	
	int _contador;
	int _frame;
public:
	ThroneLogo();
	~ThroneLogo();

	void init(int sprite);
	void update();
	void render();
};

