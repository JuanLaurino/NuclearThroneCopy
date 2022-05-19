#pragma once
#include "SDL.h"
#include "Main.h"
#define totalTeclas 9
class InputManager
{
	static InputManager* pInstance;
	SDL_Event teclas;
	bool _tecla[totalTeclas];
	bool _firstTimePressed;
public:
	InputManager();
	~InputManager();

	void update();
	void getMousePos(int* x, int* y);

	bool anyKeyPressed();
	bool getKeyPressed(int tecla);
	bool isClickJustPressed() { return _firstTimePressed; };
	void setClickJustPressedF() { _firstTimePressed = false; };

	static InputManager* getInstance();
};

