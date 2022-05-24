#pragma once
#include "GFXElement.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Bullet.h"

class GFXElementX : public GFXElement
{
protected:
	notSDL_Rect _rectFrame;
	Level* _pLevel;
	std::vector<Bullet*>* _pBullet;

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

	int _rads;
public:
	GFXElementX();
	~GFXElementX();

	void move();
	virtual void update() { move(); };
	virtual void render();

	virtual int getState() { return -1; };

	virtual void init(int sprite) {
		_spriteID = sprite;
		ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	};

	virtual void receiveDamage(int damage);
	void setWorldPointer(Level* nivel) { _pLevel = nivel; };
	void setBulletsPointer(std::vector<Bullet*>* balas) { _pBullet = balas; };
	void spawnInMap();
	void checkCollision(int direction);
	bool isOverlaping(notSDL_Rect* obj01);
	int getDamage() { return _damage; };
};

