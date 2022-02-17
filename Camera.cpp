#include "Camera.h"
#include "Level.h"
#include "Main.h"
#include "Character.h"

Camera* Camera::pInstance = nullptr;

Camera::Camera()
{
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.h = WIN_HEIGHT;
	_Rect.w = WIN_WIDTH;

	_pJugador = nullptr;
}

Camera::~Camera()
{
}

void Camera::init(Character* pJugador)
{
	_pJugador = pJugador;
	_Rect.x = _pJugador->getX() - _pJugador->getW() / 2 - WIN_WIDTH / 2;
	_Rect.y = _pJugador->getY() - _pJugador->getH() / 2 - WIN_HEIGHT / 2;
	if (_Rect.x < 0) {
		_Rect.x = 0;
	}
	else if (_Rect.x > 0) {
		_Rect.x = 0;
	}
	if (_Rect.y < 0) {
		_Rect.y = 0;
	}
	else if (_Rect.y > 0) {
		_Rect.y = 0;
	}
}

void Camera::update()
{
	_Rect.x = _pJugador->getX() - _pJugador->getW() / 2 - WIN_WIDTH / 2;
	_Rect.y = _pJugador->getY() - _pJugador->getH() / 2 - WIN_HEIGHT / 2;
}

void Camera::render()
{
}

Camera* Camera::getInstance()
{
	if (pInstance == nullptr) pInstance = new Camera();

	return pInstance;
}
