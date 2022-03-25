#include "weapon.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Video.h"
#include "Mouse.h"

extern InputManager* sInputControl;
extern Video* sVideo;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::init()
{
	_weaponType = 0;
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
		sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2);
		break;
	default:
		break;
	}
}

void Weapon::renderInventory(int posX, int posY, double angulo)
{
	switch (_state)
	{
	case ST_EQUIPED:
		sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2); // Meter en el hud

		sVideo->renderGraphicEx(_spriteID, posX, posY, _Rect.w, _Rect.h, 0, _Rect.h / 2, angulo, 0, _weaponType, 0); // Cambiar rect.h/2 por weapontype
		break;
	case ST_ON_INVENTORY:
		sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 1 + 1, _Rect.h * 2 + 2); // Meter en el hud
		break;
	default:
		break;
	}
}


