#pragma once
#include "GFXElement.h"
class Button : public GFXElement
{
	int _holdingSpriteID;
	bool _isHoldingBtn;
	int _holdingFrame;
	notSDL_Rect _spriteHoldingCollision;
	notSDL_Rect* _pMouseCollision;
public:
	Button();
	~Button();


	void init(int sprite, int holdingSprite);
	void update();
	void render();

	void setHoldingGraphicRect();
	void setHoldingGraphicID(int sprite) { _holdingSpriteID = sprite; };
	int getHoldingGraphicID() { return _spriteID; };
};

