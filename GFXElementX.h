#pragma once
#include "GFXElement.h"
#include "ResourceManager.h"
#include "Level.h"

class GFXElementX : public GFXElement
{
protected:
	notSDL_Rect _rectFrame;
	Level* _pLevel;

	int _leftSpaceInSprite;

	int _damage;
	int _HP;
	int _CD;
	bool _dir;
	bool _moving;

	int _empezarMovimiento;
	int _terminarMovimiento;

	int _CDY;
	int _CDX;	
	int _CDYT;
	int _CDXT;

	int _movX;
	int _movY;
public:
	GFXElementX();
	~GFXElementX();

	void move();
	void update() { move(); };
	void render();

	virtual void init(int sprite) {
		_spriteID = sprite;
		ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	};

	virtual void receiveDamage(int damage);
	void setWorldPointer(Level* nivel) { _pLevel = nivel; };
	void spawnInMap();
	void checkCollision(int direction);
	bool isOverlaping(notSDL_Rect* obj01);
	int getDamage() { return _damage; };
};

