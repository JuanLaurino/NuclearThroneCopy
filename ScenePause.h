#pragma once
#include "Scene.h"
#include "Button.h"

class ScenePause : public Scene
{
	GFXElement _pause;
	Button _Pbutton[3];

	int _pContador;
public:
	ScenePause();
	~ScenePause();

	void init();
	void reinit();
	void update();
	void render();
};

