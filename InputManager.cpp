#include "InputManager.h"
#include "Main.h"

InputManager* InputManager::pInstance = nullptr;

extern bool gameOn;

InputManager::InputManager()
{
	for (size_t i = 0; i < totalTeclas; i++)
	{
		_tecla[i] = false;
	}
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	while (SDL_PollEvent(&teclas)) {

		switch (teclas.type) {
		case SDL_MOUSEWHEEL:
			_tecla[I_MOUSEW] = true;
			break;
		case SDL_KEYDOWN:
			if (teclas.key.keysym.sym == Key_A) {
				_tecla[I_A] = true;
			}
			if (teclas.key.keysym.sym == Key_D) {
				_tecla[I_D] = true;
			}
			if (teclas.key.keysym.sym == Key_S) {
				_tecla[I_S] = true;
			}
			if (teclas.key.keysym.sym == Key_W) {
				_tecla[I_W] = true;
			}
			if (teclas.key.keysym.sym == Key_E) {
				_tecla[I_E] = true;
			}
			if (teclas.key.keysym.sym == Key_Space) {
				_tecla[I_SPACE] = true;
			}
			if (teclas.key.keysym.sym == Key_Escape) {
				gameOn = false;
			}
			break;
		case SDL_KEYUP:
			if (teclas.key.keysym.sym == Key_A) {
				_tecla[I_A] = false;
			}
			if (teclas.key.keysym.sym == Key_D) {
				_tecla[I_D] = false;
			}
			if (teclas.key.keysym.sym == Key_S) {
				_tecla[I_S] = false;
			}
			if (teclas.key.keysym.sym == Key_W) {
				_tecla[I_W] = false;
			}
			if (teclas.key.keysym.sym == Key_E) {
				_tecla[I_E] = false;
			}
			if (teclas.key.keysym.sym == Key_Space) {
				_tecla[I_SPACE] = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (teclas.button.button == SDL_BUTTON_LEFT) {
				_tecla[I_CLICK] = true;
				_firstTimePressed = true;
			}
			else if (teclas.button.button == SDL_BUTTON_RIGHT) {
				_tecla[I_SCLICK] = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (teclas.button.button == SDL_BUTTON_LEFT) {
				_tecla[I_CLICK] = false;
			}
			else if (teclas.button.button == SDL_BUTTON_RIGHT) {
				_tecla[I_SCLICK] = false;
			}
			break;
		case SDL_QUIT:
			gameOn = false;
			break;
		default:
			break;
		}
	}

}

void InputManager::getMousePos(int* x, int* y)
{
	SDL_GetMouseState(x, y);
}

bool InputManager::anyKeyPressed()
{
	for (size_t i = 0; i < totalTeclas; i++)
	{
		if (_tecla[i] == true) {
			return true;
		}
	}
	return false;
}

bool InputManager::getKeyPressed(int tecla)
{
	if (tecla == I_MOUSEW && _tecla[I_MOUSEW]) {
		_tecla[I_MOUSEW] = false;
		return true;
	}
	if (tecla < totalTeclas && tecla >= 0){
		return _tecla[tecla];
	}
	return false;
}

InputManager* InputManager::getInstance()
{
	if (pInstance == nullptr) pInstance = new InputManager();

	return pInstance;
}
