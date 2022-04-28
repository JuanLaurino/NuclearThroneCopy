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

	_lastDirY = 0;
	_lastDirX = 0;
	_rotation = 0;
}

Fish::~Fish()
{
}

void Fish::init()
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/characters/CharacterFish.png");
	_Rect.x = 300;
	_Rect.y = 300;
	_Rect.w = 34;
	_Rect.h = 34;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.w = 48;
	_rectFrame.h = 48;
	_canMove = true;
	_MaxHP = 6;
	_HP = 6;

	_lastDirY = 0;
	_lastDirX = 0;
	_rotation = 0;
}

void Fish::update()
{
	checkForItem();
	bool moving = false;

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

	if (_HP <= 0) {
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
		_inventory[0]->setState(ST_ON_GROUND);
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_HP = _MaxHP;
		}
		break;
	case ST_ROLL:
		_rotation+= global_elapsed_time;
		_Rect.x += _lastDirX * 1.5f;

		if (_lastDirX == MovementSpeed) {
			checkCollision(I_D);
		}
		else if (_lastDirX == -MovementSpeed) {
			checkCollision(I_A);
		}

		_Rect.y += _lastDirY * 1.5f;
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

	int weaponX = _Rect.x + _Rect.w / 2 - sCamera->getX();
	int weaponY = _Rect.y + _Rect.h - sCamera->getY();
	int delta_x = weaponX - sMouse->getX();
	int delta_y = weaponY - sMouse->getY();
	double angulo = (atan2(delta_y, delta_x) * 180) / 3.1416;

	if ((_Rect.x + (_rectFrame.w / 2) - sCamera->getX()) >= (sMouse->getX() + sMouse->getW() / 2)) { // Rotación dependiendo de donde apunta el mouse
		
		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (sMouse->getY() + sMouse->getH() / 2)) {
			_inventory[0]->renderInventory(weaponX, weaponY - 5, angulo, 2);
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 1);
			// ----
		}
		else {
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 1);
			// Render arma equipada
			_inventory[0]->renderInventory(weaponX, weaponY - 5, angulo, 2);
		}	
	}
	else {
		// Pintado arma
		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (sMouse->getY() + sMouse->getH() / 2)) {
			// Render arma equipada
			_inventory[0]->renderInventory(weaponX, weaponY, angulo, 0);
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 0);
		}
		else {
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _rotation, _rectFrame.w / 2 - 1, _rectFrame.h / 2 - 1, 0);
			// Render arma equipada
			_inventory[0]->renderInventory(weaponX, weaponY, angulo, 0);
		}
	
	}
}
