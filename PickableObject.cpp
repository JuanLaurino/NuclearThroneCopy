#include "PickableObject.h"
#include "Chest.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

PickableObject::PickableObject()
{
}

PickableObject::~PickableObject()
{
}

void PickableObject::init(int type, int posX, int posY)
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/pickable.png");
	_type = type;
	_Rect.x = posX;
	_Rect.y = posY;
	_frame = 0;

	_objState = ST_IDLE;
	_contador = 0;
	_contadorAnim = 0;
	switch (_type)
	{
	case 0:
		_rectFrame.y = 0;
		_rectFrame.x = 0;
		_Rect.h = 8;
		_Rect.w = 16;
		_rectFrame.h = _Rect.h;
		_rectFrame.w = _Rect.w;
		_rotation = rand() % 360;
		break;
	case 1:
		_rectFrame.y = 10;
		_rectFrame.x = 0;
		_Rect.h = 20;
		_Rect.w = 24;
		_rectFrame.h = _Rect.h;
		_rectFrame.w = _Rect.w;
		_rotation = rand() % 360;
		break;
	case 2:
		_rectFrame.y = 32;
		_rectFrame.x = 0;
		_Rect.h = 20;
		_Rect.w = 20;
		_rectFrame.h = _Rect.h;
		_rectFrame.w = _Rect.w;
		_rotation = 0;
		break;
	case 3:
		_rectFrame.y = 54;
		_rectFrame.x = 0;
		_Rect.h = 20;
		_Rect.w = 20;
		_rectFrame.h = _Rect.h;
		_rectFrame.w = _Rect.w;
		_rotation = 0;
		break;

	default:
		break;
	}

	_wait = rand() % 4000 + 2001;
}

void PickableObject::update()
{

	_contador += global_elapsed_time;
	switch (_objState)
	{
	case ST_IDLE:
		if (_contador >= _wait)
		{
			_objState = ST_ANIM;
			_contador = 0;
			_wait = rand() % 4000 + 2001;
			_frame = 1;
		}
		break;
	case ST_ANIM:
		if (_contador >= 160 * 5) {
			_objState = ST_IDLE;
			_frame = 0;
		}
		break;
	default:
		break;
	}
}

void PickableObject::render()
{
	switch (_objState)
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
	default:
		break;
	}
	
	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x + _frame * _rectFrame.w + _frame * 2, _rectFrame.y, _rotation, 0, 0, 0);
}

void PickableObject::moveTo(notSDL_Rect* rect)
{
	if (_Rect.x + _Rect.w / 2 <= rect->x + rect->w / 2) {
		_Rect.x+=5;
	}
	else if (_Rect.x + _Rect.w / 2 > 5 + rect->x + rect->w / 2) {
		_Rect.x-= 5;
	}
	if (_Rect.y + _Rect.h / 2 <= rect->y + rect->h / 2) {
		_Rect.y+= 5;
	}
	else if (_Rect.y + _Rect.h / 2 > 5 + rect->y + rect->h / 2) {
		_Rect.y-= 5;
	}
}
