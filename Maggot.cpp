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

void Maggot::render()
{
	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y, _Rect.w, _Rect.h, 0, 0, 0, _dir);
}

