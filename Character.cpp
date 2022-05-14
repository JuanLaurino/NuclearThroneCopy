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
	size_t size = _chest->size();
	for (size_t i = 0; i < size; i++) //Chests
	{
		if (!_chest->at(i).isOpen())
		{
			if (isOverlaping(_chest->at(i).getCollision())) {
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

	size = _weapons->size();
	for (size_t i = 0; i < size; i++)
	{
		if (_weapons->at(i)->getState() == 0)
		{
			if (isOverlaping(_weapons->at(i)->getCollision())) {
				if (sInputControl->getKeyPressed(I_E)) {
					pickUpWeapon(_weapons->at(i));
					break;
				}
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
	if (sInputControl->isClickJustPressed()) {
		switch (_inventory[0]->getType())
		{
		case 0:
			sInputControl->setClickJustPressedF();
			break;
		case 1:
			break;
		case 2:
			sInputControl->setClickJustPressedF();
			break;
		case 3:
			sInputControl->setClickJustPressedF();
			break;

		default:
			break;
		}
		
		
		Bullet* bala;
		bala = new Bullet();
		_pBullet->push_back(bala);
		_pBullet->at(_pBullet->size() - 1)->init(true, glm::vec2{ (float)(_Rect.x) + _rectFrame.w / 2, (float)(_Rect.y) + _rectFrame.h / 2 }, glm::vec2{ (float)sMouse->getX() + sCamera->getX(), (float)sMouse->getY() + sCamera->getY() }, 5, _inventory[0]->getDamage(), _inventory[0]->getWeaponSpreadAngle());
	}
}

void Character::dropWeapon() // Tira el arma que tiene equipada y se equipa la que tenía en el inventario. No puede tener 0 armas.
{
	if (_inventory[1] != nullptr) {
		_inventory[0]->setState(0);
		_inventory[0]->setXY(_Rect.x, _Rect.y);
		_inventory[0] = _inventory[1];
		_inventory[1] = nullptr;
	}
}

void Character::pickUpWeapon(Weapon* wp) // ST_ON_GROUND, ST_ON_INVENTORY, ST_EQUIPED
{
	if (_inventory[1] == nullptr) {
		_inventory[1] = _inventory[0];
		_inventory[0] = wp;

		_inventory[1]->setState(1);
		_inventory[0]->setState(2);
		return;
	}
	else {
		_inventory[0]->setState(0);
		_inventory[0]->setXY(_Rect.x, _Rect.y);

		_inventory[0] = wp;
		_inventory[0]->setState(2);
	}
	_currentShootCD = _inventory[0]->getWeaponCD();
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