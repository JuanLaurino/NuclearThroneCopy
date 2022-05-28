#include "Chest.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;

Chest::Chest()
{
	_spriteID = 0;
	_type = 0;
	_wait = 0;
	_Rect.w = 16;
	_Rect.h = 15;
	_rectFrame.y = 0;
	_rectFrame.x = 0;
	_rectFrame.h = 0;
	_rectFrame.w = 16;
	_contador = 0;
	_frame = 0;
}

Chest::~Chest()
{
}

void Chest::init(int tipo)
{
	_ammoType = 0;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/chests.png");
	_type = tipo;
	switch (_type)
	{
	case 4:
		_rectFrame.y = 65;
		_rectFrame.x = 0;
		_rectFrame.h = 16;
		_rectFrame.w = 10;
		_Rect.h = 32;
		_Rect.w = 20;
		break;
	default:
		_rectFrame.y = 15 * _type + _type;
		_rectFrame.x = 0;
		_rectFrame.h = 15;
		_rectFrame.w = 16;
		_Rect.h = 30;
		_Rect.w = 32;
		break;
	}

	_wait = rand() % 4000 + 2001;
}

void Chest::update()
{
	_contador += global_elapsed_time;
	switch (_chestState)
	{
	case ST_IDLE:
		if (_contador >= _wait)
		{
			_chestState = ST_ANIM;
			_contador = 0;
			_wait = rand() % 4000 + 2001;
			_frame = 1;
		}
		break;
	case ST_ANIM:
		if (_contador >= 160 * 5) {
			_chestState = ST_IDLE;
			_frame = 0;
		}
		break;
	case ST_OPENING:
		_frame = 1;
		if (_contador >= 160) {
			_chestState = ST_OPEN;
			_frame = 7;

			if (_type == 1) {// crea un arma
				Weapon* arma = new Weapon();
				_weapons->push_back(arma);
				arma->setXY(_Rect.x, _Rect.y);
				int randomWeapon = rand() % 3 + 1;
				arma->init(randomWeapon);
				if (randomWeapon != 3) {
					_ammoType = 0;
				}
				else {
					_ammoType = 1;
				}
			}
		}
		break;
	case ST_OPEN:
		break;
	default:
		break;
	}
}

void Chest::render()
{
	switch (_chestState)
	{
	case ST_IDLE:

		break;
	case ST_ANIM:
		_contadorAnim += global_elapsed_time;
		if (_contadorAnim >= 160) {
			_frame++;
			_contadorAnim = 0;
		}
		break;
	case ST_OPENING:

		break;
	case ST_OPEN:

		break;
	default:
		break;
	}
	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x + _frame* _rectFrame.w + _frame, _rectFrame.y, _rectFrame.w * 2, _rectFrame.h * 2, 0, 0, 0, 0);
}

void Chest::open()
{
	_chestState = ST_OPENING;
}

bool Chest::isOpen()
{
	if (_chestState == ST_OPEN) {
		return true;
	}
	return false;
}
