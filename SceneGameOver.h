#pragma once
#include "Scene.h"
#include "GFXElement.h"
#include "Button.h"

class SceneGameOver : public Scene
{
	GFXElement _gameOver;
	Button _GObutton[2];

	int _goContador;
public:
	SceneGameOver();
	~SceneGameOver();

	void init();
	void reinit();
	void update();
	void render();
};

