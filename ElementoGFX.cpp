#include "ElementoGFX.h"
#include <time.h> 
#include <stdlib.h>
#include "Video.h"
#include "ResourceManager.h"

ElementoGFX::ElementoGFX()
{
	_Rect.h = 0;
	_Rect.w = 0;
	_Rect.x = 0;
	_Rect.y = 0;
	_spriteID = 0;
}

ElementoGFX::~ElementoGFX()
{
}

void ElementoGFX::init(int sprite)
{
	_spriteID = sprite;
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
}

void ElementoGFX::update()
{
}

void ElementoGFX::render()
{
	Video::getInstance()->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h);
}

void ElementoGFX::setGraphicID(int sprite)
{
	_spriteID = sprite;
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
}

int ElementoGFX::getGraphicID()
{
	return _spriteID;
}