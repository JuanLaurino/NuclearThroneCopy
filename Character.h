#pragma once
#include "GFXElement.h"

class Character :public GFXElement
{
	enum STATES { ST_IDLE, ST_ONHIT, ST_MOVING, ST_FALLEN };

	STATES _state;
	notSDL_Rect _rectFrame;

	bool _canMove;
	int _HP;
	int _MaxHP;
	int _contador;
	int _contadorAnim;
	int _frame;
public:
	Character();
	~Character();

	void init(int sprite);
	void update();
	void render();

};

