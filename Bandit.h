#pragma once
#include "GFXElementX.h"
#include "Character.h"
#include "weapon.h"

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
	bool _flip;
	Weapon _weapon;

	Character* _pPlayer;
public:
	Bandit();
	~Bandit();

	void init();
	void update();
	void render();

	void shoot();
	void receiveDamageFromBullet(int damage, float x, float y, float speed);

	int getState() { return _state; };

	void setPlayerPointer(Character* player) { _pPlayer = player; };
};

