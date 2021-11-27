#pragma once
#include "Scene.h"
#include "Background.h"
#include "Logo.h"
#include "ThroneLogo.h"
#include "Personaje.h"

class SceneMain :public Scene
{
    bool _animationState;
    int _animation;
    int _contador;

    // Audio
    int _aMainMenuA;
    int _aMMainMenuA;
    int _aMainMenuB;
    int _aMMainMenuB;
    // ElementosGFX
    Background  _bg;
    Logo        _logo;
    ThroneLogo  _tlogo;
    ElementoGFX _escena0;
    ElementoGFX _escena1;
    ElementoGFX _escena2;

    //xd
    Personaje _personaje;
public:
    SceneMain();
    ~SceneMain();

	void init();
	void reinit();
	void update();
	void render();
};

