#pragma once
#include "GFXElementX.h"
class Cactus :public GFXElementX
{
	enum CACTUS_STATE { ST_IDLE, ST_ONHIT, ST_BROKEN };

	CACTUS_STATE _state;
	int _type;
public:
	Cactus();
	~Cactus();

	void init(int type);
	void render();

	void receiveDamage() { _state = ST_ONHIT; };
};

