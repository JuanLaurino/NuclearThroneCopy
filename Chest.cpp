#include "Chest.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

#include <stdlib.h>
#include <time.h>

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

void Chest::init(int sprite, int tipo)
{
	_spriteID = sprite;
	_type = tipo;
	switch (_type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	_rectFrame.y = 15 * _type + _type;
	_rectFrame.x = 0;
	_rectFrame.h = 15;
	_rectFrame.w = 16;
	_Rect.h = 30;
	_Rect.w = 32;

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
