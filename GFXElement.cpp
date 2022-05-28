#include "GFXElement.h"
#include <time.h> 
#include <stdlib.h>
#include "Video.h"
#include "ResourceManager.h"

GFXElement::GFXElement()
{
	_Rect.h = 0;
	_Rect.w = 0;
	_Rect.x = 0;
	_Rect.y = 0;
	_spriteID = 0;
}

GFXElement::~GFXElement()
{
}

void GFXElement::init(int sprite)
{
	_spriteID = sprite;
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
}

void GFXElement::update()
{
}

void GFXElement::render()
{
	Video::getInstance()->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h);
}

void GFXElement::moveTo(notSDL_Rect* rect)
{
}

void GFXElement::setGraphicID(int sprite)
{
	_spriteID = sprite;
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
}

int GFXElement::getGraphicID()
{
	return _spriteID;
}

int GFXElement::getDistance(notSDL_Rect* otherElement)
{
	return (int)sqrt(pow((_Rect.x + _Rect.w / 2) - (otherElement->x + otherElement->w / 2), 2) + pow((_Rect.y + _Rect.h / 2) - (otherElement->y + otherElement->h / 2), 2));
}
