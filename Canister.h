#pragma once
#include "GFXElementX.h"

class Canister : public GFXElementX
{
	enum CANISTER_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT, ST_ANIM }; // FALLEN SIEMPRE 0

	CANISTER_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
	bool _type;
	int _wait;

	std::vector<GFXElementX*>* _enemies;

public:
	Canister();
	~Canister();

	void init();
	void update();
	void render();

	void receiveDamageFromBullet(int damage, float x, float y, float speed);
	void setEnemiesPointer(std::vector<GFXElementX*>* enemies) { _enemies = enemies; };

	int getState() { return _state; };
};

