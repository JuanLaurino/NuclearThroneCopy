#include "MaggotNest.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

MaggotNest::MaggotNest()
{
}

MaggotNest::~MaggotNest()
{
}

void MaggotNest::init()
{
	_HP = 4;
	_damage = 2;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggotNest.png");
	_Rect.w = 64;
	_Rect.h = 64;
	_rectFrame.w = 64;
	_rectFrame.h = 64;
}

void MaggotNest::update()
{
}

void MaggotNest::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y);
}
