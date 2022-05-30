#include "Button.h"
#include "Video.h"
#include "ResourceManager.h"
#include "SceneDirector.h"
#include "Mouse.h"
#include "InputManager.h"

#include <iostream>

extern Mouse* sMouse;
extern InputManager* sInputControl;
extern Video* sVideo;
extern ResourceManager* sResourceManager;

Button::Button()
{
	_holdingSpriteID = 0;
	_isHoldingBtn = false;
	_holdingFrame = 0;
	_pMouseCollision = sMouse->getCollision();
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.w = 0;
	_Rect.h = 0;
}

Button::~Button()
{
}

void Button::init(int sprite, int holdingSprite)
{
	_holdingSpriteID = holdingSprite;
	_spriteID = sprite;
	sResourceManager->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	_show = true;
}

void Button::init(int sprite, bool show)
{
	_spriteID = sprite;
	sResourceManager->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	_show = show;
}

void Button::update()
{
	if (_Rect.x < _pMouseCollision->x &&
		_Rect.x + _Rect.w > _pMouseCollision->x &&
		_Rect.y < _pMouseCollision->y &&
		_Rect.h + _Rect.y > _pMouseCollision->y) {
		_isHoldingBtn = true;
	}
	else {
		_isHoldingBtn = false;
	}
}

void Button::render()
{
	if (_show) {
		if (_isHoldingBtn) {
			sVideo->renderGraphic(_holdingSpriteID, _spriteHoldingCollision.x, _spriteHoldingCollision.y, _spriteHoldingCollision.w, _spriteHoldingCollision.h, 0, _spriteHoldingCollision.h * _holdingFrame);
			if (_holdingFrame < 2) {
				//Agregar contador para que sea más lento
				_holdingFrame++;
			}
		}
		else {
			_holdingFrame = 0;
		}
		sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h);
	}
	else {
		if (_isHoldingBtn) {
			sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h);
		}
	}

}

void Button::setHoldingGraphicRect()
{
	_spriteHoldingCollision.h = 100;
	_spriteHoldingCollision.w = 300;
	_spriteHoldingCollision.x = _Rect.x;
	_spriteHoldingCollision.y = _Rect.y - _Rect.h - 10;
}
