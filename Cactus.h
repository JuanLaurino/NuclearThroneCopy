#pragma once
#include "GFXElementX.h"
class Cactus :public GFXElementX
{
	enum CACTUS_STATE { ST_BROKEN, ST_IDLE, ST_ONHIT };

	CACTUS_STATE _state;
	int _type;

	int _contador;
	int _frame;
public:
	Cactus();
	~Cactus();

	void init(int type);
	void render();


	int getState() { return _state; };
	void receiveDamage() { _state = ST_ONHIT; };
};

