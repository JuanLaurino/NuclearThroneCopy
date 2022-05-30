#pragma once
#include "Scene.h"
#include "Highscore.h"
#include "GFXElement.h"
#include "Button.h"

class SceneStats : public Scene
{
	GFXElement _stats;
	Button _SMbutton;

	int _SContador;
public:
	SceneStats();
	~SceneStats();

	void init();
	void reinit();
	void update();
	void render();
};

