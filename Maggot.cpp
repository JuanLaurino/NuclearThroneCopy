#include "Maggot.h"

#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

Maggot::Maggot()
{
}

Maggot::~Maggot()
{
}

void Maggot::init(int sprite)
{
	_spriteID = sprite;
	_rectFrame.w = 16;
	_rectFrame.h = 16;
	_Rect.w = 16;
	_Rect.h = 16;
	_leftSpaceInSprite = 1;
}

void Maggot::update()
{
	_contador += global_elapsed_time;
	switch (_state)
	{
	case Maggot::ST_IDLE:
		if (_moving) {
			_state = ST_MOVING;
			_contador = 0;
		}
		break;
	case Maggot::ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		break;
	case Maggot::ST_MOVING:
		if (!_moving) {
			_state = ST_IDLE;
			_contador = 0;
		}
		break;
	case Maggot::ST_FALLEN:
		break;
	default:
		break;
	}
}

void Maggot::render()
{

	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case Maggot::ST_IDLE:
		_rectFrame.x = 0;
		_rectFrame.y = 0;
		break;
	case Maggot::ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 1 + 1;
		break;
	case Maggot::ST_MOVING:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = 0;

		break;
	case Maggot::ST_FALLEN:
		if (_frame >= 5) {
			_frame = 5;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 1 + 1;
		break;
	default:
		break;
	}

	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y, _Rect.w, _Rect.h, 0, 0, 0, _dir);
}

void Maggot::receiveDamage(int damage)
{
	_HP = _HP - damage;
	if (_HP <= 0) {
		_state = ST_FALLEN;
	}
	else {
		_state = ST_ONHIT;
	}
}

