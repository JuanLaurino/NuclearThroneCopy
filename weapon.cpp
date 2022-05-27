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
	switch (_weaponType)
	{
	case 0:
		_cd = 180;
		_damage = 3;
		_ammoType = 0;
		_spreadAngle = 4;
		_automatic = false;
		break;
	case 1:
		_cd = 160;
		_damage = 2;
		_ammoType = 0;
		_spreadAngle = 4;
		_automatic = true;
		break;
	case 2:
		_cd = 370;
		_damage = 3;
		_ammoType = 0;
		_spreadAngle = 2;
		_automatic = false;
		break;
	case 3:
		_cd = 570;
		_damage = 2;
		_ammoType = 1;
		_spreadAngle = 20;
		_automatic = false;
		break;
	default:
		break;
	}
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/weapons.png");
	_state = ST_ON_GROUND;
	_Rect.w = 22;
	_Rect.h = 22;
	_rotation = rand() % 360;
}

void Weapon::update()
{
}

void Weapon::render()
{
	switch (_state)
	{
	case ST_ON_GROUND:
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w - 2, _Rect.h - 2, 1 + _state, 1 + _Rect.h * _weaponType + _weaponType, (int) _Rect.w * 1.5f, (int) _Rect.h * 1.5f, _rotation, _Rect.w / 2, _Rect.w / 2, 0);
		break;
	default:
		break;
	}
}

void Weapon::renderInHand(int posX, int posY, double angulo, int rotated)
{
	switch (_state)
	{
	case ST_EQUIPED:
		sVideo->renderGraphicEx(_spriteID, posX, posY - _Rect.h, _Rect.w - 4, _Rect.h - 2, 1 + _state, 1 + _Rect.h * _weaponType + _weaponType, (int) _Rect.w * 1.5f, (int) _Rect.h * 1.5f, angulo + 180, 3, 20, rotated);
		break;
	default:
		break;
	}
}

void Weapon::renderInInventory()
{
	switch (_state)
	{
	case ST_ON_INVENTORY:
		sVideo->renderGraphic(_spriteID, 120, 35, _Rect.w - 2, _Rect.h - 2, 24, 1 + _Rect.h * _weaponType + _weaponType, (int)_Rect.w * 1.5f, (int)_Rect.h * 1.5f);
		break;
	case ST_EQUIPED:
		sVideo->renderGraphic(_spriteID, 60, 35, _Rect.w - 1, _Rect.h - 2, 47, 1 + _Rect.h * _weaponType + _weaponType, (int)_Rect.w * 1.5f, (int)_Rect.h * 1.5f);
		break;
	default:
		break;
	}
}


