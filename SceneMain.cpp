#include <iostream>
#include "ResourceManager.h"
#include "AudioManager.h"
#include "Audio.h"
#include "Video.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Background.h"
#include "Main.h"
#include "SceneMain.h"
#include "SceneDirector.h"

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneMain::SceneMain()
{
    _aMainMenuA = 0;
    _aMMainMenuA = 0;
    _aMainMenuB = 0;
    _aMMainMenuB = 0;
    _animation = 0;
    mReinit = true;
    _animationState = false;
    _contador = false;
}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
    mReinit = false;
    _animationState = true;

    // Audio
    _aMainMenuA = sAudioManager->loadAndGetAudioID("Assets/sound/musThemeA.ogg");
    _aMMainMenuA = -1;
    _aMainMenuB = sAudioManager->loadAndGetAudioID("Assets/sound/musThemeB.ogg");
    _aMMainMenuB = -1;

    // ElementosGFX
    sMouse->init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/cursor.png"));
    _bg.init();
    _logo.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/AMenu.png"));
    _tlogo.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/AThrone.png"));
    _escena0.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena0.png"));
    _escena1.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena1.png"));
    _escena2.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena2.png"));
}

void SceneMain::reinit()
{
    mReinit = true;
}

void SceneMain::update() {
    //Clear Screen
    sVideo->clearScreen();

    if (_animationState) { //Animación antes del menú
        std::cout << "Animation: " << _animation << std::endl;
        if (_aMMainMenuA == -1) { // Si aún no comenzó menuA
            _aMMainMenuA = Audio::getInstance()->playAudio(-1, _aMainMenuA, 0);
        }
        if (_animation < 4) {
            if ((_contador * global_elapsed_time) > 4000 || (((_contador * global_elapsed_time) > 200) && sInputControl->anyKeyPressed())) {
                _animation++;
                _contador = 0;
            }
            _tlogo.update();
        }
        else {//Ultima imagen y animación, puede darle a cualquier tecla para ir al menu principal
            _bg.update();
            if ((((_contador * global_elapsed_time) > 400) && sInputControl->anyKeyPressed())) {
                _animationState = false;
                _contador = 0;
            }
        }

        _contador++;
        _logo.update();
    }
    else {  // Menú
        _bg.update();

        if ((sInputControl->getKeyPressed(I_A))) {
            sDirector->changeScene(SELECT_CHARACTER, 1);
        }
    }

    if (!sAudio->isPlaying(_aMMainMenuA) && _aMMainMenuB == -1) { //Si menuA terminó de reproducirse y aún no empezó menub
        _aMMainMenuB = sAudio->playAudio(-1, _aMainMenuB, 999);
    }
    //Mouse
    sMouse->update();
}

void SceneMain::render() {

    if (_animationState) {
        switch (_animation)
        {
        case 0:
            _escena0.render();
            break;
        case 1:
            _escena1.render();
            break;
        case 2:
            _escena2.render();
            break;
        case 3:
            _tlogo.render();
            break;
        case 4:
            _bg.render();
            _logo.render();
            break;
        default:
            break;
        }
    }
    else {
        _bg.render();
    }
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}