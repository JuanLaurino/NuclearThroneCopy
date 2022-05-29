#pragma once
#include "GFXElementX.h"
#include "Character.h"

class BigMaggot : public GFXElementX
{
	enum BMAGGOT_STATE { ST_FALLEN, ST_IDLE, ST_ONHIT, ST_MOVING }; // FALLEN SIEMPRE 0

	BMAGGOT_STATE _state;

	int _contador;
	int _contadorAnim;
	int _frame;
	int _viewDistance;

	Character* _pPlayer;
	std::vector<GFXElementX*>* _enemies;
public:
	BigMaggot();
	~BigMaggot();

	void init();
	void update();
	void render();

	void receiveDamageFromBullet(int damage, float x, float y, float speed);
	int getState() { return _state; };

	void setPlayerPointer(Character* player) { _pPlayer = player; };
	void setEnemiesPointer(std::vector<GFXElementX*>* enemies) { _enemies = enemies; };
};

