#pragma once
#include "GFXElementX.h"
class Portal :public GFXElementX
{
	int _contador;
	int _contadorAnim;
	int _frame;

	bool _open;
	bool _active;
public:
	Portal();
	~Portal();

	void init();
	void update();
	void render();

	void setOpen(bool open) { _open = open; };
	bool getActive() { return _active; };
};

