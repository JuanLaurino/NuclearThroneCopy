#include "weapon.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Video.h"
#include "Mouse.h"

extern InputManager* sInputControl;
extern Video* sVideo;

weapon::weapon()
{
}

weapon::~weapon()
{
}

void weapon::update()
{
	switch (_state)
	{
	case ST_ON_GROUND:
		if (sInputControl->getKeyPressed(I_E)) {
			_state = ST_EQUIPED;
		}
		break;
	case ST_EQUIPED:
		if (sInputControl->getKeyPressed(I_SPACE)) {
			_state = ST_ON_INVENTORY;
		}
		if (sInputControl->getKeyPressed(I_E)) {
			_state = ST_ON_GROUND;
			// _Rect.x = jugador.x
			// _Rect.y = jugador.y
		}
		break;
	case ST_ON_INVENTORY:
		if (sInputControl->getKeyPressed(I_SPACE)) {
			_state = ST_EQUIPED;
		}
		break;
	default:
		break;
	}
}

void weapon::render()
{
	switch (_state)
	{
	case ST_ON_GROUND:
		sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2);
		break;
	case ST_EQUIPED:
		sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2); // Meter en el hud

		//sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 2 + 2, _Rect.h * 2 + 2);
		break;
	case ST_ON_INVENTORY:
		sVideo->renderGraphic(_spriteID, 0, 0, _Rect.w, _Rect.h, _Rect.w * 1 + 1, _Rect.h * 2 + 2); // Meter en el hud
		break;
	default:
		break;
	}
}
