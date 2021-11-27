#pragma once
#include "ElementoGFX.h"
class Personaje :public ElementoGFX
{
	enum STATES { ST_IDLE, ST_CHARGING, ST_IN_ALERT, ST_CHANGING_DIRECTION, ST_JUMPING, ST_FALLEN, ST_FALLING };
	STATES _state;
	bool _direction;
	int _contador;
	int _contadorAnim;
	int _frame;
	notSDL_Rect _rectFrame;
public:
	Personaje();
	~Personaje();

	void init(int sprite);
	void update();
	void render();

};

