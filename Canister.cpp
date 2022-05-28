#include "Canister.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Main.h"
#include "Camera.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Camera*			sCamera;

extern Uint32           global_elapsed_time;

Canister::Canister()
{
}

Canister::~Canister()
{
}

void Canister::init()
{
	_type = rand() % 2;

	if (_type == 0) {
		_damage = 0;
		_rads = 0;
		_HP = 2;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/canister.png");
		_rectFrame.w = 10;
		_rectFrame.h = 16;
		_Rect.w = _rectFrame.w;
		_Rect.h = _rectFrame.h;
	}
	else {
		_damage = 2;
		_rads = 0;
		_HP = 4;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/canister2.png");
		_rectFrame.w = 18;
		_rectFrame.h = 22;
		_Rect.w = _rectFrame.w;
		_Rect.h = _rectFrame.h;
	}

	_state = ST_IDLE;

}

void Canister::update()
{
	switch (_state)
	{
	case Canister::ST_FALLEN:
		break;
	case Canister::ST_IDLE:
		break;
	case Canister::ST_ONHIT:
		break;
	default:
		break;
	}
}

void Canister::render()
{
}
