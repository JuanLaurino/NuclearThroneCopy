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
	_Rect.x = (_pJugador->getX() - (_pJugador->getW() / 2)) - (WIN_WIDTH / 2);
	_Rect.y = (_pJugador->getY() - (_pJugador->getH() / 2)) - (WIN_HEIGHT / 2);

	if (_Rect.x < 33) {
		_Rect.x = 33;
	}
	else if (_Rect.x > 2048 - WIN_WIDTH) {//  cambiar 2048 por variable del ancho del mapa 
		_Rect.x = 2048 - WIN_WIDTH;
	}

	if (_Rect.y < 33) {
		_Rect.y = 33;
	}
	else if (_Rect.y > 448 - WIN_HEIGHT) {//  cambiar 480 por variable del alto del mapa
		_Rect.y = 448 - WIN_HEIGHT;
	}
}

void Camera::update()
{	
	_Rect.x = (_pJugador->getX() + (_pJugador->getW() / 2)) - (WIN_WIDTH / 2);
	_Rect.y = (_pJugador->getY() + (_pJugador->getH() / 2)) - (WIN_HEIGHT / 2);

	if (_Rect.x < 0) {
		_Rect.x = 0;
	}
	else if (_Rect.x > (2048 - WIN_WIDTH)) {//  cambiar 2048 por variable del ancho del mapa 
		_Rect.x = 2048 - WIN_WIDTH;
	}

	if (_Rect.y < 0) {
		_Rect.y = 0;
	}
	else if (_Rect.y > (448 - WIN_HEIGHT)) {//  cambiar 480 por variable del alto del mapa
		_Rect.y = 448 - WIN_HEIGHT;
	}
}

void Camera::render()
{
}

Camera* Camera::getInstance()
{
	if (pInstance == nullptr) pInstance = new Camera();

	return pInstance;
}
