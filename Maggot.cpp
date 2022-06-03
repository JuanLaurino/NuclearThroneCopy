#include "Maggot.h"
#include "Highscore.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include "KeyDefine.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Highscore*		sHighscore;

Maggot::Maggot()
{
}

Maggot::~Maggot()
{
}

void Maggot::init(int type)
{
	if (type == 0) {
		_damage = 1;
		_rads = 1;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggot.png");
	}
	else {
		_damage = 2;
		_rads = 3;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/radMaggot.png");
	}

	_HP = 2;
	_state = ST_IDLE;
	_rectFrame.w = 16;
	_rectFrame.h = 16;
	_Rect.w = (int)_rectFrame.w * 1.5;
	_Rect.h = (int)_rectFrame.h * 1.5;
	_leftSpaceInSprite = 1;
}

void Maggot::update()
{
	_contador += global_elapsed_time;
	if (_state != ST_FALLEN && _state != ST_ONHIT) {
		move();
	}
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
		if (_contador <= 100 + _corpseSpeed * 5) {
			_Rect.x += (int)round(_corpseSpeed * _XVector);
			if (_XVector > 0) {
				checkCollisionBounce(I_D);
			}
			else {
				checkCollisionBounce(I_A);
			}


			_Rect.y += (int)round(_corpseSpeed * _YVector);
			if (_YVector > 0) {
				checkCollisionBounce(I_S);
			}
			else {
				checkCollisionBounce(I_W);
			}
		}
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

	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, _dir);
}

void Maggot::receiveDamageFromBullet(int damage, float x, float y, float speed)
{
	if (_state != ST_FALLEN) {
		_HP = _HP - damage;

		if (_HP <= 0) {
			_state = ST_FALLEN;
			_frame = 0;
			_contadorAnim = 0;
			_contador = 0;
			// Spawn rads
			spawnRads(_rads);
			_XVector = x;
			_YVector = y;
			if (speed >= 500) {
				_corpseSpeed = 1;
			}
			else if (speed >= 400) {
				_corpseSpeed = 3;
			}
			else if (speed >= 300) {
				_corpseSpeed = 5;
			}
			else if (speed >= 200) {
				_corpseSpeed = 7;
			}
			else {
				_corpseSpeed = 10;
			}

			if (rand() % 20 == 0) { // 5% chance de que spawnee un objeto
				if (rand() % 2) {
					spawnObject(0);
				}
				else {
					spawnObject(1);
				}
			}
		}
		else {
			_state = ST_ONHIT;
			_frame = 0;
			_contadorAnim = 0;
			_contador = 0;
		}
	}
}

