#pragma once
#include "GFXElementX.h"
class Maggot : public GFXElementX
{
	enum MAGGOT_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT, ST_MOVING }; // FALLEN SIEMPRE 0

	MAGGOT_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
public:
	Maggot();
	~Maggot();

	void init(int type);
	void update();
	void render();

	void receiveDamage(int damage);
	int getState() { return _state; };
};

