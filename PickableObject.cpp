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
	switch (_type)
	{
	case 0:
		_rectFrame.y = 0;
		_rectFrame.x = 0;
		_rectFrame.h = 4;
		_rectFrame.w = 8;
		_Rect.h = 8;
		_Rect.w = 16;
		break;
	case 1:
		_rectFrame.y = 6;
		_rectFrame.x = 0;
		_rectFrame.h = 10;
		_rectFrame.w = 12;
		_Rect.h = 20;
		_Rect.w = 22;
		break;
	case 2:
		_rectFrame.y = 17;
		_rectFrame.x = 0;
		_rectFrame.h = 10;
		_rectFrame.w = 10;
		_Rect.h = 20;
		_Rect.w = 20;
		break;
	case 3:
		_rectFrame.y = 28;
		_rectFrame.x = 0;
		_rectFrame.h = 10;
		_rectFrame.w = 10;
		_Rect.h = 20;
		_Rect.w = 20;
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
	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x + _frame * _rectFrame.w + _frame, _rectFrame.y, _rectFrame.w * 2, _rectFrame.h * 2, 0, 0, 0, 0);
}
