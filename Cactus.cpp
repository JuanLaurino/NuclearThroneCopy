#include "Cactus.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

Cactus::Cactus()
{
	_type = 0;
	_contador = 0;
	_frame = 0;
}

Cactus::~Cactus()
{
}

void Cactus::init(int type)
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/cactus.png");
	_type = type;
	_rectFrame.w = 21;
	_rectFrame.h = 23;
	_Rect.w = _rectFrame.w * 2;
	_Rect.h = _rectFrame.h * 2;
}

void Cactus::render()
{
	switch (_state)
	{	
	case Cactus::ST_ONHIT:
		_contador += global_elapsed_time;
		_frame = 1;
		if (_contador >= 320) {
			_state = ST_BROKEN;
			_contador = 0;
		}
		else if (_contador != 160) {
			_frame = 2;
		}
		break;
	case Cactus::ST_BROKEN:
		_frame = 3;
		break;
	default:
		break;
	}

	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 3, _rectFrame.h - 2, _frame * _rectFrame.w + _frame * 2, _type * _rectFrame.h + _type + 1, _Rect.w, _Rect.h);
}
