#pragma once
#include "GFXElement.h"
#include "Character.h"
#include "Level.h"

class Camera :public GFXElement
{
	static Camera* pInstance;
	Character* _pJugador;
	Level* _pMapa;

	int _contador;
	int _offsetX;
	int _offsetY;
public:
	Camera();
	~Camera();

	void init(Character* pJugador, Level* mapa);
	void update();
	void shake();

	static Camera* getInstance();
};