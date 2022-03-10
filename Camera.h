#pragma once
#include "GFXElement.h"
#include "Character.h"
#include "Level.h"

class Camera :public GFXElement
{
	static Camera* pInstance;
	Character* _pJugador;
	Level* _pMapa;
public:
	Camera();
	~Camera();

	void init(Character* pJugador, Level* mapa);
	void update();

	static Camera* getInstance();
};