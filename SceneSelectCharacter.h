#pragma once
#include "Scene.h"
class SceneSelectCharacter : public Scene
{
	GFXElement _selectCharacterIMG;
public:
	SceneSelectCharacter();
	~SceneSelectCharacter();

	void init();
	void reinit();
	void update();
	void render();
};

