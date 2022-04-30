#pragma once
#include "GFXElement.h"
#include "ResourceManager.h"
#include "Level.h"

class GFXElementX : public GFXElement
{
protected:
	notSDL_Rect _rectFrame;
	int _damage;
	int _HP;
	int _CD;
	bool _dir;

	int _empezarMovimiento;
	int _terminarMovimiento;

	int _CDY;
	int _CDX;	
	int _CDYT;
	int _CDXT;

	bool _movX;
	bool _movY;
public:
	GFXElementX();
	~GFXElementX();

	void move();
	void render();

	virtual void init(int sprite) {
		_spriteID = sprite;
		ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	};
	void spawnInMap(Level* pNivel);
	bool isOverlaping(notSDL_Rect* obj01);
	int getDamage() { return _damage; };
};

