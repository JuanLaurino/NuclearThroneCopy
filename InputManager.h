#pragma once
#include "SDL.h"
#include "Main.h"

class InputManager
{
	static InputManager* pInstance;
	SDL_Event teclas;
	bool _tecla[8];
public:
	InputManager();
	~InputManager();
	void update();
	void getMousePos(int* x, int* y);
	bool anyKeyPressed();
	bool getKeyPressed(int tecla);
	static InputManager* getInstance();
};

