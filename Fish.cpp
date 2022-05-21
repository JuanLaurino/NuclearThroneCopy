#include "Fish.h"
#include "Video.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "Camera.h"
#include "Mouse.h"
#include <iostream>

extern InputManager* sInputControl;
extern Video* sVideo;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;
extern Mouse* sMouse;
extern ResourceManager* sResourceManager;

Fish::Fish()
{
	_fishState = ST_IDLE;
	_contador = 0;
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.w = 0;
	_Rect.h = 0;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 0;
	_rectFrame.h = 0;
	_frame = 0;
	_contadorAnim = 0;
	_HP = 0;
	_MaxHP = 0;

	_canMove = false;
	_canReceiveDamage = true;

	_lastDirY = 0;
	_lastDirX = 0;
	_rotation = 0;

	_shootCD = 200;
	_currentShootCD = _shootCD;
}

Fish::~Fish()
{
}

void Fish::init()
{	
	_leftSpaceInSprite = 7;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/characters/CharacterFish.png");
	_Rect.w = 34;
	_Rect.h = 34;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 48;
	_rectFrame.h = 48;
	_canMove = true;
	_MaxHP = 8;
	_HP = 8;
	_ammo[0] = 180;

	_lastDirY = 0;
	_lastDirX = 0;
	_rotation = 0;
	_actionCD = 0;
}

void Fish::update()
{
	_actionCD -= global_elapsed_time;
	if (_actionCD < 0) _actionCD = 0;
	if (sInputControl->getKeyPressed(I_MOUSEW) && _actionCD <= 0 && _inventory[1] != NULL) {
		swapWeapon();
		_actionCD = 300;
	}

	checkForItem();
	receiveDamage();
	bool moving = false;

	_currentShootCD -= global_elapsed_time;
	if (_shootBlocked == 0) {
		if (_fishState != ST_FALLEN && _fishState != ST_ROLL) {
			if (sInputControl->getKeyPressed(I_CLICK) && _currentShootCD <= 0) {
				_currentShootCD = _inventory[0]->getWeaponCD();
			
				if (_ammo[_inventory[0]->getWeaponAmmoType()] > 0) {
					if (sInputControl->isClickJustPressed()) {
						switch (_inventory[0]->getType())
						{
						case 0:
							sInputControl->setClickJustPressedF();
							_ammo[_inventory[0]->getWeaponAmmoType()] -= 1;
							shoot();
							break;
						case 1:
							_ammo[_inventory[0]->getWeaponAmmoType()] -= 1;
							shoot();
							break;
						case 2:
							sInputControl->setClickJustPressedF();
							_ammo[_inventory[0]->getWeaponAmmoType()] -= 3;
							_shootBlocked = 200;
							_amountShoot = 3;
							break;
						case 3:
							sInputControl->setClickJustPressedF();
							_ammo[_inventory[0]->getWeaponAmmoType()] -= 1;
							shoot();
							break;

						default:
							break;
						}
					}
				}
			}
		}
	}
	else {
		if (_shootBlocked == 200) {
			shoot();
			_amountShoot--;
		}
		_shootBlocked -= global_elapsed_time;
		if (_shootBlocked <= 0) {
			_shootBlocked = 0;
			shoot();
			_amountShoot--;
			if (_amountShoot > 0) {
				_shootBlocked = 199;
			}
		}
		_currentShootCD = _inventory[0]->getWeaponCD();
	}

	if (_canMove) {
		if (sInputControl->getKeyPressed(I_D) && _Rect.x < (_pLevel->getMapWidth() - _rectFrame.w + 1)) {
			_Rect.x += MovementSpeed;
			_lastDirX = MovementSpeed;
			checkCollision(I_D);
			moving = true;
		}
		else if (sInputControl->getKeyPressed(I_A) && _Rect.x > -1) {
			_Rect.x -= MovementSpeed;
			_lastDirX = -MovementSpeed;
			checkCollision(I_A);
			moving = true;
		}
		else {
			_lastDirX = 0;
		}

		if (sInputControl->getKeyPressed(I_W) && _Rect.y > -1) {
			_Rect.y -= MovementSpeed;
			_lastDirY = -MovementSpeed;
			checkCollision(I_W);
			moving = true;
		}
		else if (sInputControl->getKeyPressed(I_S) && _Rect.y < (_pLevel->getMapHeight() - _rectFrame.h + 1)) {
			_Rect.y += MovementSpeed;
			_lastDirY = MovementSpeed;
			checkCollision(I_S);
			moving = true;
		}
		else {
			_lastDirY = 0;
		}
	}
	_contador += global_elapsed_time;

	if (_HP <= 0 && _fishState != ST_FALLEN) {
		_contador = 0;

		_fishState = ST_FALLEN;
		_frame = 0;
		_canMove = false;
	}

	switch (_fishState)
	{
	case ST_IDLE:
		if (moving) {
			_contador = 0;

			_fishState = ST_MOVING;
			_frame = 0;
		}
		break;
	case ST_MOVING:
		if (!moving) {
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
		}
		if (sInputControl->getKeyPressed(I_SPACE)) {
			_contador = 0;

			_fishState = ST_ROLL;
			_frame = 0;
			_canMove = false;
		}
		break;
	case ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
		}
		break;
	case ST_FALLEN:
		if (_inventory[0] != nullptr) {
			_inventory[0]->setState(ST_ON_GROUND);
			_inventory[0]->setXY(_Rect.x + rand() % 20, _Rect.y + rand() % 20);
			_inventory[0] = nullptr;
		}
		if (_inventory[1] != nullptr) {
			_inventory[1]->setState(ST_ON_GROUND);
			_inventory[1]->setXY(_Rect.x + rand() % 20, _Rect.y + rand() % 20);
			_inventory[1] = nullptr;
		}
		/*
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_HP = _MaxHP;
		}*/
		break;
	case ST_ROLL:
		_rotation+= global_elapsed_time;
		_Rect.x += (int)(_lastDirX * 1.5f);
		if (_Rect.x < 0) _Rect.x = 0;
		if (_Rect.x >= _pLevel->getMapWidth()) _Rect.x = _pLevel->getMapWidth()-1;

		if (_lastDirX == MovementSpeed) {
			checkCollision(I_D);
		}
		else if (_lastDirX == -MovementSpeed) {
			checkCollision(I_A);
		}

		_Rect.y += (int)(_lastDirY * 1.5f);
		if (_Rect.y < 0) _Rect.y = 0;
		if (_Rect.y >= _pLevel->getMapHeight()) _Rect.y = _pLevel->getMapHeight() - 1;
		if (_lastDirY == MovementSpeed) {
			checkCollision(I_S);
		}
		else if (_lastDirY == -MovementSpeed) {
			checkCollision(I_W);
		}

		if (_contador > 450) { 
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_rotation = 0;
		}
		break;
	default:
		break;
	}
}

void Fish::render()
{
	_contadorAnim += global_elapsed_time;
	switch (_fishState)
	{
	case ST_IDLE:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 2 + 4;
		break;
	case ST_MOVING:
		if (_frame >= 6) {
			_frame = 0;
		}
		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 3 + 6;
		break;
	case ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 4 + 8;
		break;
	case ST_FALLEN:
		if (_frame >= 2) {
			_frame = 2;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 5 + 10;
		break;
	case ST_ROLL:
		_rectFrame.x = _rectFrame.w * 1 + 2;
		_rectFrame.y = _rectFrame.h * 3 + 6;
		break;
	default:
		break;
	}
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	if (_fishState == ST_FALLEN) {
		if (_flip) {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 1);
		}
		else {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 0);
		}
		return;
	}

	int weaponX = _Rect.x + _Rect.w / 2 - sCamera->getX();
	int weaponY = _Rect.y + _Rect.h - sCamera->getY();
	int delta_x = weaponX - sMouse->getX();
	int delta_y = weaponY - sMouse->getY();
	double angulo = (atan2(delta_y, delta_x) * 180) / 3.1416;
	// Rotacion de la bala?
	_flip = (_Rect.x + (_rectFrame.w / 2) - sCamera->getX()) >= (sMouse->getX() + sMouse->getW() / 2);
	if (_flip) { // Rotación dependiendo de donde apunta el mouse
		
		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (sMouse->getY() + sMouse->getH() / 2)) {
			_inventory[0]->renderInHand(weaponX, weaponY - 5, angulo, 2);
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 1);
			// ----
		}
		else {
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 1);
			// Render arma equipada
			_inventory[0]->renderInHand(weaponX, weaponY - 5, angulo, 2);
		}	
	}
	else {
		// Pintado arma
		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (sMouse->getY() + sMouse->getH() / 2)) {
			// Render arma equipada
			_inventory[0]->renderInHand(weaponX, weaponY, angulo, 0);
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 0);
		}
		else {
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 0);
			// Render arma equipada
			_inventory[0]->renderInHand(weaponX, weaponY, angulo, 0);
		}
	
	}
}

void Fish::receiveDamage()
{
	if (_canReceiveDamage) {
		if (_fishState != ST_ONHIT && _fishState != ST_FALLEN && _fishState != ST_ROLL)
		{
			size_t size = _enemies->size();
			for (size_t i = 0; i < size; i++)
			{
				if (_enemies->at(i)->getState() != 0) { // Si el enemigo no está muerto (State 0 es siempre muerto)
					if (isOverlaping(_enemies->at(i)->getCollision())) {
						_HP -= _enemies->at(i)->getDamage();
						_fishState = ST_ONHIT;
						_canReceiveDamage = false;
						break;
					}
				}
			}
		}
	}
	else {
		_contadorRDaño += global_elapsed_time;
		if (_contadorRDaño >= 160) {
			_canReceiveDamage = true;
			_contadorRDaño = false;
		}
	}
}
