#include "Character.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Camera.h"
#include "Mouse.h"
#include <iostream>

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Mouse*			sMouse;

Character::Character()
{
	_state = ST_IDLE;
	_contador = 0;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 0;
	_rectFrame.h = 0;
	_frame = 0;
	_contadorAnim = 0;
	_HP = 0;
	_MaxHP = 0;
	_canMove = false;
}

Character::~Character()
{
}

void Character::init(int sprite) {
	_spriteID = sprite;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 48;
	_rectFrame.h = 48;
	_Rect.x = (WIN_WIDTH / 2) - (_rectFrame.w / 2); // + 50
	_Rect.y = (WIN_HEIGHT / 2) - (_rectFrame.h / 2);
	_canMove = true;
	_MaxHP = 6;
	_HP = 6;
}

void Character::update()
{
	bool moving = false;

	if (_canMove) {
		if (sInputControl->getKeyPressed(I_D) && _Rect.x < (1160 - _rectFrame.w)) {
			_Rect.x +=3;
			moving = true;
		}
		if (sInputControl->getKeyPressed(I_A) && _Rect.x > 0) {
			_Rect.x -= 3;
			moving = true;
		}
		if (sInputControl->getKeyPressed(I_W) && _Rect.y > 0) {
			_Rect.y -= 3;
			moving = true;
		}
		if (sInputControl->getKeyPressed(I_S) && _Rect.y < (1160 - _rectFrame.h)) {
			_Rect.y += 3;
			moving = true;
		}
	}
	_contador+= global_elapsed_time;

	if (_HP <= 0) { 
		_contador = 0;

		_state = ST_FALLEN;
		_frame = 0;
		_canMove = false;
	}

	switch (_state)
	{
	case ST_IDLE:
		if (moving) {
			_contador = 0;
			
			_state = ST_MOVING;
			_frame = 0;
		}
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG//gothit
			_contador = 0;

			_state = ST_ONHIT;
			_frame = 0;
			_canMove = false;
			_HP--;
		}
		break;
	case ST_MOVING:
		if (!moving) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG //gothit
			_contador = 0;

			_state = ST_ONHIT;
			_frame = 0;
			_canMove = false;
			_HP--;
		}
		break;
	case ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
			_canMove = true;
		}
		break;
	case ST_FALLEN:
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG
			_contador = 0;
		
			_state = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_HP = _MaxHP;
		}
		break;
	default:
		break;
	}
}

void Character::render()
{
	_contadorAnim+=global_elapsed_time;
	switch (_state)
	{
	case ST_IDLE:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 2 + 4;
		break;
	case ST_MOVING:
		if (_frame >= 6) {
			_frame = 0;
		}
		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 3 + 6;
		break;
	case ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}
		
		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 4 + 8;
		break;
	case ST_FALLEN:
		if (_frame >= 2) {
			_frame = 2;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 5 + 10;
		break;
	default:
		break;
	}
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}
	
	if ((_Rect.x + (_rectFrame.w / 2) - sCamera->getX()) >= (sMouse->getX() + sMouse->getW() / 2)) {
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, 0, 0, 0, 1);
	}
	else {
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, 0, 0, 0, 0);
	}
}