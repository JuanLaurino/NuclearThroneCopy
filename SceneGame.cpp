#include "SceneGame.h"
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
#include "Camera.h"
#include <iostream>

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;
extern Camera*          sCamera;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{
}

void SceneGame::init()
{
    mReinit = false;
    _nivel.init("Assets/levelBasico.tmx", sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/tileset_level.png"));
    _personaje.init();
    _personaje.setWorldPointer(&_nivel);
    sCamera->init(&_personaje, &_nivel);

    //Prueba
    arma01.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/weapons.png"));
    arma01.setXY(430,270);

    for (size_t i = 0; i < 4; i++)
    {
        _chest[i].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/chests.png"), i);
        _chest[i].spawnInMap(&_nivel);
    }

    //Prueba
    _personaje.setWeapon00(&arma01);
    //prueba

    _personaje.spawnInMap(&_nivel);
    _maggots.resize(20); // ERROR
    for (size_t i = 0; i < 20; i++)
    {
        _maggots[i].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggot.png"));
        _maggots[i].spawnInMap(&_nivel);
    }
}

void SceneGame::reinit()
{
    mReinit = false;
}

void SceneGame::update()
{
    if (sInputControl->getKeyPressed(I_SCLICK)) {
        sVideo->setFullScreen(true);
    }
    if (sInputControl->getKeyPressed(I_CLICK)) {
        sVideo->setFullScreen(false);
    }

    //Clear Screen
    sVideo->clearScreen();

    _nivel.update();

    for (size_t i = 0; i < 20; i++)
    {
        _maggots[i].update();
    }
    _personaje.update();
    sCamera->update();
    sMouse->update();

    //if ((sInputControl->getKeyPressed(I_A))) {
    //    sDirector->changeScene(GAME_OVER, 1);
    //}
}

void SceneGame::render()
{
    sVideo->setRenderColor(245, 189, 81);

    sMouse->render();
    _nivel.render();    

    for (size_t i = 0; i < 4; i++)
    {
        _chest[i].render();
    }
    for (size_t i = 0; i < 20; i++)
    {
        _maggots[i].render();
    }
    _personaje.render();
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
