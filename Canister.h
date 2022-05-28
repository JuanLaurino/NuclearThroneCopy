#pragma once
#include "GFXElementX.h"
class Canister : public GFXElementX
{
	enum CANISTER_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT }; // FALLEN SIEMPRE 0

	CANISTER_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
	bool _type;
public:
	Canister();
	~Canister();

	void init();
	void update();
	void render();
};

