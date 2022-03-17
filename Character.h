#pragma once
#include "GFXElement.h"
#include "Level.h" // borrar?

#define MovementSpeed 3

class Character :public GFXElement
{
protected:
	enum PLAYER_STATE { ST_IDLE, ST_ONHIT, ST_MOVING, ST_FALLEN };

	PLAYER_STATE _state;
	notSDL_Rect _rectFrame;

	bool _canMove;
	int _HP;
	int _MaxHP;
	int _contador;
	int _contadorAnim;
	int _frame;

	Level* _pLevel;
public:
	Character();
	~Character();

	void checkCollision(int direction);
	void setWorldPointer(Level* nivel);
};

