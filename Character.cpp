#include "Character.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Camera.h"
#include "Mouse.h"
#include <iostream>

extern InputManager*	sInputControl;
extern Video*			sVideo;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Mouse*			sMouse;
extern ResourceManager* sResourceManager;

Character::Character()
{
	_shootCD = 20;
	_currentShootCD = _shootCD;
	_maxAmmo[0] = 255;
	for (size_t i = 1; i < 5; i++)
	{
		_maxAmmo[i] = 55;
	}
}

Character::~Character()
{
}

void Character::checkForItem()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (isOverlaping(_chest->at(i).getCollision()) && !_chest->at(i).isOpen()) {
			_chest->at(i).open();
			switch (_chest->at(i).getType())
			{
			case 0: // Cofre ammo
				addAmmo(rand() % 5);
				break;
			case 1: // Cofre arma-ammo
				addAmmo(rand() % 5); // Cambiar por ammo del tipo del arma que sale del cofre
				break;
			case 2: // Cofre vida
				addHP(4);
				break;
			case 3:
				switch (rand() % 5)
				{
				case 0:
					addAmmo(rand() % 5);
					addAmmo(rand() % 5);
					break;
				case 1:
					addHP(4);
					break;
				case 2:
					addAmmo(rand() % 5);
					addHP(2);
					break;
				case 3:
					addAmmo(rand() % 5);
					addHP((rand() % 2 + 1) * 2);
					break;
				case 4:
					addHP(6);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Character::receiveDamage()
{
	if (_state != ST_ONHIT && _state != ST_FALLEN)
	{
		size_t size = _enemies->size();
		for (size_t i = 0; i < size; i++)
		{
			if (isOverlaping(_enemies->at(i)->getCollision())) {
				_HP -= _enemies->at(i)->getDamage();
				_state = ST_ONHIT;
				break;
			}
		}
	}
}

void Character::shoot()
{
	_inventory[0]->getType();
	Bullet* bala;
	bala = new Bullet();
	_pBullet->push_back(bala);
	_pBullet->at(_pBullet->size() - 1)->init(true, glm::vec2{ (float)(_Rect.x ) + _rectFrame.w / 2, (float)(_Rect.y ) + _rectFrame.h / 2 }, glm::vec2{ (float)sMouse->getX() + sCamera->getX(), (float)sMouse->getY() + sCamera->getY() }, 5, 1);
}

void Character::addHP(short amount)
{
	_HP += amount;
	if (_HP > _MaxHP) {
		_HP = _MaxHP;
	}
}

void Character::addAmmo(short type)
{
	if (type == 0) {
		_ammo[type] += 60;
	}
	else {
		_ammo[type] += 12;
	}

	if (_ammo[type] > _maxAmmo[type]) {
		_ammo[type] = _maxAmmo[type];
	}
}
