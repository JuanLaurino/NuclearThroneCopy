#pragma once
#include "GFXElement.h"
class ThroneLogo :public GFXElement
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

