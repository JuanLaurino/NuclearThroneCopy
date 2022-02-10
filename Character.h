#pragma once
#include "GFXElement.h"

class Character :public GFXElement
{
	enum STATES { ST_IDLE, ST_CHARGING, ST_IN_ALERT, ST_CHANGING_DIRECTION, ST_JUMPING, ST_FALLEN, ST_FALLING };
	STATES _state;
	bool _direction;
	int _contador;
	int _contadorAnim;
	int _frame;
	notSDL_Rect _rectFrame;
public:
	Character();
	~Character();

	void init(int sprite);
	void update();
	void render();

};

