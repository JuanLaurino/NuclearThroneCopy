#pragma once
#include "Scene.h"
class SceneSelectCharacter : public Scene
{
public:
	SceneSelectCharacter();
	~SceneSelectCharacter();

	void init();
	void reinit();
	void update();
	void render();
};

