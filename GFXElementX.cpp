#include "GFXElementX.h"

#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


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
	_damage = 1;
	_HP = 1;
	_CD = 0;

	_empezarMovimiento = rand() % 2000 + 500;
	_terminarMovimiento = rand() % 4000 + 1000;
	_movX = rand() % 3 - 1;
	_movY = rand() % 3 - 1;

	_CDXT = rand() % 50;
	_CDYT = rand() % 80;
}

GFXElementX::~GFXElementX()
{
}

void GFXElementX::move() // FALTA COLISION
{
	_CD += global_elapsed_time;
	if (_CD >= _terminarMovimiento) {
		_CD = 0;
		_empezarMovimiento = rand() % 2000 + 500;
		_terminarMovimiento = rand() % 4000 + 1000;
		_movX = rand() % 3 - 1;
		_movY = rand() % 3 - 1;
		
		_CDXT = rand() % 50;
		_CDYT = rand() % 80;
	}
	if (_CD > _empezarMovimiento) { // Los hace más lentos
		_CDX += global_elapsed_time;
		_CDY += global_elapsed_time;
		if (_CDX >= _CDXT) {
			_CDX = 0;
			_Rect.x += _movX;
		}
		if (_CDY >= _CDYT) {
			_CDY = 0;
			_Rect.y += _movY;
		}
	}
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
