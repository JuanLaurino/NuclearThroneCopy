#pragma once
#include "GFXElementX.h"
#include "Character.h"

class Bandit : public GFXElementX
{
	enum BANDIT_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT, ST_MOVING, ST_ATTACKING }; // FALLEN SIEMPRE 0

	BANDIT_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
	int _spreadAngle;
	int _viewDistance;
	int _shootCD;

	Character* _pPlayer;
public:
	Bandit();
	~Bandit();

	void init();
	void update();
	void render();

	void shoot();
	void receiveDamage(int damage);

	void setPlayerPointer(Character* player) { _pPlayer = player; };
};

