#include "Character.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Camera.h"
#include "Mouse.h"
#include <iostream>

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Mouse*			sMouse;
extern ResourceManager* sResourceManager;

Character::Character()
{
}

Character::~Character()
{
}

void Character::checkForItem()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (isOverlaping(_chest->at(i).getCollision())) {
			_chest->at(i).open();
		}
	}
}

void Character::checkCollision(int direction)
{
	switch (direction)
	{
	case I_D:
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7 + _Rect.w, _Rect.y + 7)){
			_Rect.x--;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7 + _Rect.w, _Rect.y + 7 + _Rect.h)){
			_Rect.x--;
		}
		break;
	case I_A:
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7, _Rect.y + 7)) {
			_Rect.x++;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7, _Rect.y + 7 + _Rect.h)) {
			_Rect.x++;
		}
		break;
	case I_W:
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7, _Rect.y + 7)) {
			_Rect.y++;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7 + _Rect.w, _Rect.y + 7)) {
			_Rect.y++;
		}
		break;
	case I_S:
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7, _Rect.y + 7 + _Rect.h)) {
			_Rect.y--;
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + 7 + _Rect.w, _Rect.y + 7 + _Rect.h)) {
			_Rect.y--;
		}
		break;
	default:
		break;
	}
	//std::cout << _Rect.x << " - " << _Rect.y << std::endl;
}

void Character::setChestPointer(std::vector<Chest>* chest)
{
	_chest = chest;
}

void Character::setMaggotPointer(Maggot* maggots[20])
{
}

void Character::setWorldPointer(Level* nivel)
{
	_pLevel = nivel;
}