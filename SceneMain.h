#pragma once
#include "Scene.h"
#include "Background.h"
#include "Logo.h"
#include "ThroneLogo.h"
#include "Button.h"

class SceneMain :public Scene
{
    bool _animationState;
    int _currentScene;
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
    GFXElement _escena[3];
    Button _button[5];
    
public:
    SceneMain();
    ~SceneMain();

	void init();
	void reinit();
	void update();
	void render();
};

