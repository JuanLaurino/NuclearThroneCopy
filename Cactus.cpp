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
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, 0, _type * _rectFrame.h + _type + 1, _Rect.w, _Rect.h);
}
