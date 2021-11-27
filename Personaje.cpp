#include "Personaje.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include <iostream>

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Uint32           global_elapsed_time;

Personaje::Personaje()
{
	_direction = false;
	_state = ST_IDLE;
	_contador = 0;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 0;
	_rectFrame.h = 0;
}

Personaje::~Personaje()
{
}

void Personaje::init(int sprite) {
	_spriteID = sprite;
	_Rect.x = (WIN_WIDTH / 2) - (_rectFrame.w / 2);
	_Rect.y = (WIN_HEIGHT / 2) - (_rectFrame.h / 2);
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 96;
	_rectFrame.h = 96;
}

void Personaje::update()
{
	_contador++;
	switch (_state)
	{
	case ST_IDLE:
		if (sInputControl->getKeyPressed(I_A)) {
			_contador = 0;
			
			_state = ST_IN_ALERT;
		}
		else if ((_contador * global_elapsed_time) > 4000) {
			_contador = 0;

			_state = ST_CHANGING_DIRECTION;
		}
		break;
	case ST_CHANGING_DIRECTION:
		if ((_contador * global_elapsed_time) > 1000) {
			_contador = 0;
			_direction = !_direction;

			_state = ST_IDLE;
		}
		break;
	case ST_CHARGING:
		if (sInputControl->getKeyPressed(I_SPACE)) {
			_contador = 0;

			_state = ST_JUMPING;
		}
		else if (sInputControl->getKeyPressed(I_D)) {
			_contador = 0;

			_state = ST_FALLING;
		}
		break;
	case ST_FALLEN:
		if ((_contador * global_elapsed_time) > 3000) {
			_contador = 0;

			_state = ST_IDLE;
		}
		break;
	case ST_FALLING:
		if ((_contador * global_elapsed_time) > 4000) { 
			_contador = 0;

			_state = ST_FALLEN;
		}
		break;
	case ST_IN_ALERT:
		if ((_contador * global_elapsed_time) > 1000) {
			_contador = 0;
			_state = ST_CHARGING;
		}
		break;
	case ST_JUMPING:
		if (!(sInputControl->getKeyPressed(I_SPACE))) {
			_contador = 0;

			_state = ST_CHARGING;
		}
		break;
	default:
		break;
	}
}

void Personaje::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y);
}
