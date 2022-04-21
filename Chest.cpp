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
}

Chest::~Chest()
{
}

void Chest::init(int sprite, int prueba)
{
	_spriteID = sprite;

	_rectFrame.y = 15 * prueba + prueba;
	_rectFrame.x = 0;
	_rectFrame.h = 15;
	_rectFrame.w = 16;
}

void Chest::render()
{
	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, _rectFrame.w * 2, _rectFrame.h * 2, 0, 0, 0, 0);
}
