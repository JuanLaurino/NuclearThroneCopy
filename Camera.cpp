#include "Camera.h"
#include "Level.h"
#include "Main.h"
#include "Character.h"
#include "Level.h"
#include "Mouse.h"

Camera* Camera::pInstance = nullptr; 
extern Mouse* sMouse;

Camera::Camera()
{
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.h = WIN_HEIGHT;
	_Rect.w = WIN_WIDTH;

	_pJugador = nullptr;
	_pMapa = nullptr;
}

Camera::~Camera()
{
}

void Camera::init(Character* pJugador, Level* mapa)
{
	_pJugador = pJugador;
	_pMapa = mapa;
	_Rect.x = (_pJugador->getX() - (_pJugador->getW() / 2)) - (WIN_WIDTH / 2);
	_Rect.y = (_pJugador->getY() - (_pJugador->getH() / 2)) - (WIN_HEIGHT / 2);

	if (_Rect.x < 40) {
		_Rect.x = 40;
	}
	else if (_Rect.x > (_pMapa->getMapWidth() * _pMapa->getWidth() - 1) - WIN_WIDTH) {
		_Rect.x = (_pMapa->getMapWidth() * _pMapa->getWidth() - 1) - WIN_WIDTH;
	}

	if (_Rect.y < 40) {
		_Rect.y = 40;
	}
	else if (_Rect.y > (_pMapa->getMapHeight() * _pMapa->getHeight() - 1) - WIN_HEIGHT) {
		_Rect.y = (_pMapa->getMapHeight() * _pMapa->getHeight() - 1) - WIN_HEIGHT;
	}
}

void Camera::update()
{	
	_Rect.x = (_pJugador->getX() + (_pJugador->getW() / 2)) - (WIN_WIDTH / 2)  + sMouse->getX() / 3 - (WIN_WIDTH / 6);
	_Rect.y = (_pJugador->getY() + (_pJugador->getH() / 2)) - (WIN_HEIGHT / 2) + sMouse->getY() / 3 - (WIN_HEIGHT / 6);

	if (_Rect.x < 0) {
		_Rect.x = 0;
	}
	else if (_Rect.x > (_pMapa->getMapWidth() - 1) - WIN_WIDTH) {
		_Rect.x = (_pMapa->getMapWidth() - 1) - WIN_WIDTH;
	}

	if (_Rect.y < 0) {
		_Rect.y = 0;
	}
	else if (_Rect.y > (_pMapa->getMapHeight() - 1) - WIN_HEIGHT) {
		_Rect.y = (_pMapa->getMapHeight() - 1) - WIN_HEIGHT;
	}
}

Camera* Camera::getInstance()
{
	if (pInstance == nullptr) pInstance = new Camera();

	return pInstance;
}
