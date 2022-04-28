#include "GFXElementX.h"

#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

GFXElementX::GFXElementX()
{
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 0;
	_rectFrame.w = 0;
}

GFXElementX::~GFXElementX()
{
}

void GFXElementX::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y);
}

void GFXElementX::spawnInMap(Level* pNivel)
{
	bool canSpawn;
	do
	{
		canSpawn = true;
		_Rect.x = rand() % pNivel->getMapWidth();
		_Rect.y = rand() % pNivel->getMapHeight();

		if (pNivel->getIDfromLayer(0, _Rect.x, _Rect.y)) {
			canSpawn = false;
			continue;
		}
		if (pNivel->getIDfromLayer(0, _Rect.x + _rectFrame.w, _Rect.y)) {
			canSpawn = false;
			continue;
		}
		if (pNivel->getIDfromLayer(0, _Rect.x, _Rect.y + _rectFrame.h)) {
			canSpawn = false;
			continue;
		}
		if (pNivel->getIDfromLayer(0, _Rect.x + _rectFrame.w, _Rect.y + _rectFrame.h)) {
			canSpawn = false;
			continue;
		}

	} while (!canSpawn);
}

bool GFXElementX::isOverlaping(notSDL_Rect* obj01)
{
	if (obj01->x < _Rect.x + _Rect.w &&
		obj01->x + obj01->w > _Rect.x &&
		obj01->y < _Rect.y + _Rect.h &&
		obj01->h + obj01->y > _Rect.y) {
		return true;
	}
	return false;
}
