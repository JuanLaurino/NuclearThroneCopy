#pragma once
#include "GFXElement.h"
#include "Character.h"

class Camera :public GFXElement
{
	static Camera* pInstance;
	Character* _pJugador;
public:
	Camera();
	~Camera();

	void init(Character* pJugador);
	void update();
	void render();

	static Camera* getInstance();
};