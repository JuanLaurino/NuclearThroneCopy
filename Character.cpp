#include "Character.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include <iostream>

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Uint32           global_elapsed_time;

Character::Character()
{
	_direction = false;
	_state = ST_IDLE;
	_contador = 0;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 0;
	_rectFrame.h = 0;
	_frame = 0;
	_contadorAnim = 0;
}

Character::~Character()
{
}

void Character::init(int sprite) {
	_spriteID = sprite;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 96;
	_rectFrame.h = 96;
	_Rect.x = (WIN_WIDTH / 2) - (_rectFrame.w / 2);
	_Rect.y = (WIN_HEIGHT / 2) - (_rectFrame.h / 2);
}

void Character::update()
{
	_contador++;
	switch (_state)
	{
	case ST_IDLE:
		if (sInputControl->getKeyPressed(I_A)) {
			_contador = 0;
			
			_state = ST_IN_ALERT;
			_frame = 0;
		}
		else if ((_contador * global_elapsed_time) > 4000) {
			_contador = 0;

			_state = ST_CHANGING_DIRECTION;
			_frame = 0;
		}
		break;
	case ST_CHANGING_DIRECTION:
		if ((_contador * global_elapsed_time) > 700) {
			_contador = 0;
			_direction = !_direction;

			_state = ST_IDLE;
			_frame = 0;
		}
		break;
	case ST_CHARGING:
		if (sInputControl->getKeyPressed(I_SPACE)) {
			_contador = 0;

			_state = ST_JUMPING;
			_frame = 0;
		}
		else if (sInputControl->getKeyPressed(I_D)) {
			_contador = 0;

			_state = ST_FALLING;
			_frame = 0;
		}
		break;
	case ST_FALLEN:
		if ((_contador * global_elapsed_time) > 3000) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		break;
	case ST_FALLING:
		if ((_contador * global_elapsed_time) > 900) { 
			_contador = 0;

			_state = ST_FALLEN;
			_frame = 0;
		}
		break;
	case ST_IN_ALERT:
		if ((_contador * global_elapsed_time) > 1000) {
			_contador = 0;
			_state = ST_CHARGING;
			_frame = 0;
		}
		break;
	case ST_JUMPING:
		if (!(sInputControl->getKeyPressed(I_SPACE))) {
			_contador = 0;

			_state = ST_CHARGING;
			_frame = 0;
		}
		break;
	default:
		break;
	}
}

void Character::render()
{
	_contadorAnim++;
	switch (_state)
	{
	case ST_IDLE:
		if (_frame >= 3) {
			_frame = 0;
		}
		_rectFrame.y = 0;
		if (_direction) {
			_rectFrame.x = 96 * _frame;
		}
		else {
			_rectFrame.x = (96*3) + (96 * _frame);
		}
		break;
	case ST_CHANGING_DIRECTION:
		if (_frame >= 5) {
			_frame = 0;
		}
		_rectFrame.y = 96 * 6;
		if (!_direction) {
			_rectFrame.x = 96 * _frame;
		}
		else {
			_rectFrame.x = (96 * 4) - (96 * _frame);
		}
		break;
	case ST_CHARGING:
		if (_frame >= 6) {
			_frame = 0;
		}
		
		if (_direction) {
			_rectFrame.y = 96;
			_rectFrame.x = 96 * _frame;
		}
		else {
			_rectFrame.y = 96 * 2;
			_rectFrame.x = (96 * 5) - (96 * _frame);
		}
		break;
	case ST_FALLEN:
		if (_frame >= 4) {
			_frame = 0;
		}

		_rectFrame.x = (96 * 5) - (96 * _frame);
		if (_direction) {
			_rectFrame.y = 96 * 3;
		}
		else {
			_rectFrame.y = 96 * 4;
		}
		break;
	case ST_FALLING:
		if (_frame >= 6) {
			_frame = 0;
		}

		_rectFrame.x = 96 * _frame;
		if (_direction) {
			_rectFrame.y = 96 * 3;
		}
		else {
			_rectFrame.y = 96 * 4;
		}
		break;
	case ST_IN_ALERT:
		if (_frame >= 3) {
			_frame = 0;
		}
		_rectFrame.y = 96 * 5;
		if (_direction) {
			_rectFrame.x = 96 * _frame;
		}
		else {
			_rectFrame.x = (96 * 3) + (96 * _frame);
		}
		break;
	case ST_JUMPING:
		_rectFrame.y = 96 * 7;
		if (_direction) {
			_rectFrame.x = 96;
		}
		else {
			_rectFrame.x = 0;
		}
		break;
	default:
		break;
	}
	if (_contadorAnim * global_elapsed_time > 160) {
		_frame++;
		_contadorAnim = 0;
	}
	sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y);
}
