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
    _currentScene = 0;
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
    _aMainMenuA = sAudioManager->loadAndGetAudioID("Assets/music/musThemeA.ogg");
    _aMMainMenuA = -1;
    _aMainMenuB = sAudioManager->loadAndGetAudioID("Assets/music/musThemeB.ogg");
    _aMMainMenuB = -1;

    // ElementosGFX
    sMouse->init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/cursor.png"));
    _bg.init();
    _logo.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/AMenu.png"));
    _tlogo.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/AThrone.png"));
    _escena[0].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena0.png"));
    _escena[1].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena1.png"));
    _escena[2].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/escena2.png"));

    // Botones
    _button[0].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/playButton.png"), sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(),"Assets/menu/holdingButton.png"));
    _button[0].setXY(WIN_WIDTH / 2 - _button[0].getW() / 2, 0  + WIN_HEIGHT / 2 - 100);
    _button[0].setHoldingGraphicRect();

    _button[1].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/coopButton.png"), sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(),"Assets/menu/holdingButton.png"));
    _button[1].setXY(WIN_WIDTH / 2 - _button[1].getW() / 2, 40 + WIN_HEIGHT / 2 - 100);
    _button[1].setHoldingGraphicRect();

    _button[2].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/settingsButton.png"), sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/holdingButton.png"));
    _button[2].setXY(WIN_WIDTH / 2 - _button[2].getW() / 2, 80 + WIN_HEIGHT / 2 - 100);
    _button[2].setHoldingGraphicRect();

    _button[3].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/statsButton.png"), sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/holdingButton.png"));
    _button[3].setXY(WIN_WIDTH / 2 - _button[3].getW() / 2, 120 + WIN_HEIGHT / 2 - 100);
    _button[3].setHoldingGraphicRect();

    _button[4].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/quitButton.png"), sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/holdingButton.png"));
    _button[4].setXY(WIN_WIDTH / 2 - _button[4].getW() / 2, 160 + WIN_HEIGHT / 2 - 100);
    _button[4].setHoldingGraphicRect();
}

void SceneMain::reinit()
{
    mReinit = true;
}

void SceneMain::update() {
    // QUITAR
    if ((sInputControl->getKeyPressed(I_D))) { 
        sDirector->changeScene(GAME, 1);
    }
    // QUITAR
    // 
    //Clear Screen
    sVideo->clearScreen();

    if (_animationState) { //Animación antes del menú
        std::cout << "Animation: " << _currentScene << std::endl;
        if (_aMMainMenuA == -1) { // Si aún no comenzó menuA
            _aMMainMenuA = Audio::getInstance()->playAudio(-1, _aMainMenuA, 0);
        }
        if (_currentScene < 4) {
            if ((_contador * global_elapsed_time) > 4000 || (((_contador * global_elapsed_time) > 200) && sInputControl->anyKeyPressed())) {
                _currentScene++;
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
        
        for (size_t i = 0; i < 5; i++)
        {
            _button[i].update();
        }

        if ((sInputControl->getKeyPressed(I_CLICK) && _button[0].getIsHoldingBtn())) { //Si le da a PLAY
            //sDirector->changeScene(SELECT_CHARACTER, 1);
            sDirector->changeScene(GAME, 1); // QUITAR Y METER SELECT CHARACTER
        }
        if ((sInputControl->getKeyPressed(I_CLICK) && _button[3].getIsHoldingBtn())) { //Si le da a STATS
            sDirector->changeScene(STATS, 1);
        }
        if ((sInputControl->getKeyPressed(I_CLICK) && _button[4].getIsHoldingBtn())) { //Si le da a QUIT
            gameOn = false;
        }

        if (sAudio->isPlaying(_aMMainMenuA)) { //Si la canción A está activa, cuando se entra al menú principal se cierra y se abre la canción B
            _aMMainMenuB = sAudio->playAudio(-1, _aMainMenuB, 999);
            sAudio->stopAudio(_aMMainMenuA);
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
        if (_currentScene < 3) {
            _escena[_currentScene].render();
        }
        else if (_currentScene == 3) {
            _tlogo.render();
        }
        else {
            _bg.render();
            _logo.render();
        }
    }
    else { // Menú
        _bg.render();

        for (size_t i = 0; i < 5; i++)
        {
            _button[i].render();
        }
    }
    //Render mouse
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}