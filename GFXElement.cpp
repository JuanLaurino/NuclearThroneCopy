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

void GFXElement::setGraphicID(int sprite)
{
	_spriteID = sprite;
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
}

int GFXElement::getGraphicID()
{
	return _spriteID;
}