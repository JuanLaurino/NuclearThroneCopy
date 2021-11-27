#include "Mouse.h"
#include "InputManager.h"
#include "Video.h"

Mouse* Mouse::pInstance = nullptr;

Mouse::Mouse()
{
	mouseCol.h = 1;
	mouseCol.w = 1;
	_Rect.h = 0;
	_Rect.w = 0;
	_Rect.x = 0;
	_Rect.y = 0;
	_spriteID = 0;
}

Mouse::~Mouse()
{
}

void Mouse::update()
{
	InputManager::getInstance()->getMousePos(&_Rect.x,&_Rect.y);
}

void Mouse::render()
{
	// Pinto desde el centro de la imagen
	Video::getInstance()->renderGraphic(_spriteID, _Rect.x - 15, _Rect.y - 15, _Rect.w, _Rect.h);
}

Mouse* Mouse::getInstance()
{
	if (pInstance == nullptr) pInstance = new Mouse();

	return pInstance;
}