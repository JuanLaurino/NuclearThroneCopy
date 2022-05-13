#include "weapon.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Video.h"
#include "Mouse.h"
#include "Camera.h"
#include <stdlib.h>
#include <time.h> 

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Camera*			sCamera;
extern Mouse*			sMouse;
extern ResourceManager* sResourceManager;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::init(int weaponType)
{
	_weaponType = weaponType;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/weapons.png");
	_state = ST_ON_GROUND;
	_Rect.w = 22;
	_Rect.h = 22;
	rotation = rand() % 360;
}

void Weapon::update()
{
	switch (_state)
	{
	case ST_ON_GROUND:
		break;
	case ST_EQUIPED:
		break;
	case ST_ON_INVENTORY:
		break;
	default:
		break;
	}
}

void Weapon::render()
{
	switch (_state)
	{
	case ST_ON_GROUND:
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w - 2, _Rect.h - 2, 1 + _state, 1 + _Rect.h * _weaponType + _weaponType, (int) _Rect.w * 1.5f, (int) _Rect.h * 1.5f, rotation, _Rect.w / 2, _Rect.w / 2, 0);
		break;
	default:
		break;
	}
}

void Weapon::renderInventory(int posX, int posY, double angulo, int rotated)
{
	switch (_state)
	{
	case ST_ON_INVENTORY:
		//sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 1 + 1, _Rect.h * 2 + 2); //arreglar numeros
		break;
	case ST_EQUIPED:
		//sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2);

		sVideo->renderGraphicEx(_spriteID, posX, posY - _Rect.h, _Rect.w - 4, _Rect.h - 2, 1 + _state, 1 + _Rect.h * _weaponType + _weaponType, (int) _Rect.w * 1.5f, (int) _Rect.h * 1.5f, angulo + 180, 3, 20, rotated);
		break;
	default:
		break;
	}
}


