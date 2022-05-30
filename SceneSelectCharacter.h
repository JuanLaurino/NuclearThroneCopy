#pragma once
#include "Scene.h"
#include "GFXElement.h"
#include "Button.h"

class SceneSelectCharacter : public Scene
{
	GFXElement _selectCharacterIMG;
	Button _SCbutton[4];


	int _SCcontador;
public:
	SceneSelectCharacter();
	~SceneSelectCharacter();

	void init();
	void reinit();
	void update();
	void render();
};

