#include "GFXElementX.h"

#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Main.h"


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

void GFXElementX::move()
{
	_CD += global_elapsed_time;
	if (_CD >= _terminarMovimiento) {
		_moving = false;
		_CD = 0;
		_empezarMovimiento = rand() % 1000 + 300;
		_terminarMovimiento = rand() % 2000 + 1000;
		_movX = ((rand() % 30) - 10) / 10;
		_movY = ((rand() % 30) - 10) / 10;
		
		_CDXT = rand() % 50;
		_CDYT = rand() % 80;
	}
	if (_CD > _empezarMovimiento) { // Los hace más lentos
		_moving = true;
		_CDX += global_elapsed_time;
		_CDY += global_elapsed_time;
		if (_CDX >= _CDXT) {
			_CDX = 0;
			if (_movX > 0) {
				_dir = true;
			}
			else if (_movX < 0) {
				_dir = false;
			}
			_Rect.x += _movX;
			if (_movX > 0) {
				checkCollision(I_D);
			}
			else {
				checkCollision(I_A);
			}
		}
		if (_CDY >= _CDYT) {
			_CDY = 0;
			_Rect.y += _movY;

			if (_movY > 0) {
				checkCollision(I_S);
			}
			else {
				checkCollision(I_W);
			}
		}
	}
}

void GFXElementX::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y);
}

void GFXElementX::receiveDamage(int damage)
{
	_HP -= damage;
}

void GFXElementX::spawnInMap()
{
	bool canSpawn;
	do
	{
		canSpawn = true;
		_Rect.x = rand() % _pLevel->getMapWidth();
		_Rect.y = rand() % _pLevel->getMapHeight();

		if (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y)) {
			canSpawn = false;
			continue;
		}
		if (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y)) {
			canSpawn = false;
			continue;
		}
		if (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y + _Rect.h)) {
			canSpawn = false;
			continue;
		}
		if (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y + _Rect.h)) {
			canSpawn = false;
			continue;
		}

	} while (!canSpawn);
}

void GFXElementX::checkCollision(int direction)
{
	switch (direction)
	{
	case I_D:
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite + _Rect.w, _Rect.y + _leftSpaceInSprite)) {
			_Rect.x--;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite + _Rect.w, _Rect.y + _leftSpaceInSprite + _Rect.h)) {
			_Rect.x--;
		}
		break;
	case I_A:
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite, _Rect.y + _leftSpaceInSprite)) {
			_Rect.x++;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite, _Rect.y + _leftSpaceInSprite + _Rect.h)) {
			_Rect.x++;
		}
		break;
	case I_W:
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite, _Rect.y + _leftSpaceInSprite)) {
			_Rect.y++;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite + _Rect.w, _Rect.y + _leftSpaceInSprite)) {
			_Rect.y++;
		}
		break;
	case I_S:
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite, _Rect.y + _leftSpaceInSprite + _Rect.h)) {
			_Rect.y--;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _leftSpaceInSprite + _Rect.w, _Rect.y + _leftSpaceInSprite + _Rect.h)) {
			_Rect.y--;
		}
		break;
	default:
		break;
	}
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
