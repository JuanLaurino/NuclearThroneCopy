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
	bool _dir;
	bool _moving;
	int _empezarMovimiento;
	int _terminarMovimiento;

	int _CD;
	int _CDY;
	int _CDX;	
	int _CDYT;
	int _CDXT;

	float _XVector;
	float _YVector;
	float _corpseSpeed;

	int _movX;
	int _movY;

	int _rads;

	std::vector<GFXElement*>* _objects;
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
	virtual void receiveDamageFromBullet(int damage, float x, float y, float speed);

	void setWorldPointer(Level* nivel) { _pLevel = nivel; };
	void setBulletsPointer(std::vector<Bullet*>* balas) { _pBullet = balas; };
	void setObjectPointer(std::vector<GFXElement*>* objects) { _objects = objects; };

	void spawnRads(int amount);
	void spawnObject(bool hpdrop);

	void spawnInMap();
	void checkCollision(int direction);
	bool isOverlaping(notSDL_Rect* obj01);
	int getDamage() { return _damage; };
};

