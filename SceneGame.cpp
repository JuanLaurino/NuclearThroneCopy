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
    _chest.resize(0);
    _enemies.resize(0);
    _bullets.resize(0);
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
    _personaje.setBulletsPointer(&_bullets);
    sCamera->init(&_personaje, &_nivel);

    _cactus.resize(rand() % 10);
    size_t size = _cactus.size();
    for (size_t i = 0; i < size; i++)
    {
        _cactus[i].init(rand() % 3);
        _cactus[i].setWorldPointer(&_nivel);
        _cactus[i].spawnInMap();
    }

    //Prueba
    arma01.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/weapons.png"));
    arma01.setWorldPointer(&_nivel);
    arma01.spawnInMap();
    arma02.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/object/weapons.png"));
    arma02.setWorldPointer(&_nivel);
    arma02.spawnInMap();

    Chest *cofre;
    for (size_t i = 0; i < 4; i++)
    {
        cofre = new Chest();
        _chest.push_back(*cofre);
        _chest[i].init(i);
        _chest[i].setWorldPointer(&_nivel);
        _chest[i].spawnInMap();
    }

    //Prueba
    _personaje.setWeapon00(&arma01);
    _personaje.setWeapon01(&arma02);
    //prueba

    _personaje.spawnInMap();
    Maggot* maggot;
    for (size_t i = 0; i < 15; i++)
    {
        maggot = new Maggot();
        _enemies.push_back(maggot);
        _enemies[i]->init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggot.png"));
        _enemies[i]->setWorldPointer(&_nivel);
        _enemies[i]->spawnInMap();
    }
    _personaje.setChestPointer(&_chest);
    _personaje.setEnemiesPointer(&_enemies);
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

    size_t size = _chest.size();
    for (size_t i = 0; i < size; i++)
    {
        _chest[i].update();
    }
    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        _enemies[i]->update();
    } 
    size = _bullets.size();
    for (size_t i = 0; i < size; i++)
    {
        _bullets[i]->update();
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

    size_t size = _cactus.size();
    for (size_t i = 0; i < size; i++)
    {
        _cactus[i].render();
    }

    size = _chest.size();
    for (size_t i = 0; i < size; i++)
    {
        _chest[i].render();
    }
    arma01.render();
    arma02.render();
    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        _enemies[i]->render(); //receive dmg
        for (size_t j = 0; j < _bullets.size(); j++) // Bullet.size porque el número puede cambiar
        {
            if (_enemies[i]->isOverlaping(_bullets[j]->getCollision()) && _enemies[i]->getState() != 0) {
                _enemies[i]->receiveDamage(_bullets[j]->getDamage());
                _bullets.erase(_bullets.begin() + j);
            }
        }
    }

    _personaje.render();
    size = _bullets.size();
    for (size_t i = 0; i < size; i++)
    {
        _bullets[i]->render();
    }


    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
