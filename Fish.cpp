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
}

void Fish::update()
{

	bool moving = false;

	if (_canMove) {
		if (sInputControl->getKeyPressed(I_D) && _Rect.x < (1160 - _rectFrame.w)) {
			_Rect.x += MovementSpeed;
			_lastDirX = MovementSpeed;
			checkCollision(I_D);
			moving = true;
		}
		else if (sInputControl->getKeyPressed(I_A) && _Rect.x > 0) {
			_Rect.x -= MovementSpeed;
			_lastDirX = -MovementSpeed;
			checkCollision(I_A);
			moving = true;
		}
		else {
			_lastDirX = 0;
		}

		if (sInputControl->getKeyPressed(I_W) && _Rect.y > 0) {
			_Rect.y -= MovementSpeed;
			_lastDirY = -MovementSpeed;
			checkCollision(I_W);
			moving = true;
		}
		else if (sInputControl->getKeyPressed(I_S) && _Rect.y < (1160 - _rectFrame.h)) {
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
		//if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG//gothit
		//	_contador = 0;
		//
		//	_fishState = ST_ONHIT;
		//	_frame = 0;
		//	_canMove = false;
		//	_HP--;
		//}
		break;
	case ST_MOVING:
		if (!moving) {
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
		}
		//if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG //gothit
		//	_contador = 0;
		//
		//	_fishState = ST_ONHIT;
		//	_frame = 0;
		//	_canMove = false;
		//	_HP--;
		//}
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG //gothit
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
		if (sInputControl->getKeyPressed(I_SPACE)) { // 4 DEBUG
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_HP = _MaxHP;
		}
		break;
	case ST_ROLL:
		_Rect.x += _lastDirX;
		if (_lastDirX == MovementSpeed) {
			checkCollision(I_D);
		}
		else if (_lastDirX == -MovementSpeed) {
			checkCollision(I_A);
		}

		_Rect.y += _lastDirY;
		if (_lastDirY == MovementSpeed) {
			checkCollision(I_S);
		}
		else if (_lastDirY == -MovementSpeed) {
			checkCollision(I_W);
		}

		if (sInputControl->getKeyPressed(I_E)) { // QUITARRRRRR
			_contador = 0;

			_fishState = ST_IDLE;
			_frame = 0;
			_canMove = true;
			_HP = _MaxHP;
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
		//HACERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR (animación :p)
		break;
	default:
		break;
	}
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	if ((_Rect.x + (_rectFrame.w / 2) - sCamera->getX()) >= (sMouse->getX() + sMouse->getW() / 2)) {
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, 0, 0, 0, 1);
	}
	else {
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, 0, 0, 0, 0);
	}
}
