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
}

GFXElementX::~GFXElementX()
{
}

void GFXElementX::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, 0, 0);
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
		if (pNivel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y)) {
			canSpawn = false;
			continue;
		}
		if (pNivel->getIDfromLayer(0, _Rect.x, _Rect.y + _Rect.h)) {
			canSpawn = false;
			continue;
		}
		if (pNivel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y + _Rect.h)) {
			canSpawn = false;
			continue;
		}

	} while (!canSpawn);
}
