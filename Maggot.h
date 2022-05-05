#pragma once
#include "GFXElementX.h"
class Maggot : public GFXElementX
{
	enum MAGGOT_STATE { ST_IDLE, ST_ONHIT, ST_MOVING, ST_FALLEN };

	MAGGOT_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
public:
	Maggot();
	~Maggot();

	void init(int sprite);
	void update();
	void render();
	void receiveDamage(int damage);
};

