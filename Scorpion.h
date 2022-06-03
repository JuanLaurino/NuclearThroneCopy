#pragma once
#include "GFXElementX.h"
#include "Character.h"

class Scorpion : public GFXElementX
{
	enum SCORPION_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT, ST_MOVING, ST_ATTACKING }; // FALLEN SIEMPRE 0

	SCORPION_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
	int _spreadAngle;
	int _viewDistance;
	int _shootCD;
	bool _flip;
	bool _shootTwoTimes;

	Character* _pPlayer;
public:
	Scorpion();
	~Scorpion();

	void init();
	void update();
	void render();

	void shoot();
	void receiveDamageFromBullet(int damage, float x, float y, float speed);

	int getState() { return _state; };

	void setPlayerPointer(Character* player) { _pPlayer = player; };
};
