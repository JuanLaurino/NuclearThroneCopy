#pragma once
#include "GFXElementX.h"

class MaggotNest : public GFXElementX
{
	enum MAGGOTNEST_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT }; // FALLEN SIEMPRE 0

	MAGGOTNEST_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;

	std::vector<GFXElementX*>* _enemies;

public:
	MaggotNest();
	~MaggotNest();

	void init();
	void update();
	void render();

	void receiveDamage(int damage);
	void setEnemiesPointer(std::vector<GFXElementX*>* enemies) { _enemies = enemies; };
};

