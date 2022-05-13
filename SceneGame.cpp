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
#include "MaggotNest.h"
#include "Highscore.h"

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;
extern Camera*          sCamera;
extern Highscore*       sHighscore;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneGame::SceneGame()
{
    _chest.resize(0);
    _enemies.resize(0);
    _bullets.resize(0);
    _weapons.resize(0);
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
    _personaje.setWeaponPointer(&_weapons);
    _personaje.setChestPointer(&_chest);
    _personaje.setEnemiesPointer(&_enemies);

    _hud.setPlayerPointer(&_personaje);
    _hud.init();

    sCamera->init(&_personaje, &_nivel);

    _cactus.resize(rand() % 15);
    size_t size = _cactus.size();
    for (size_t i = 0; i < size; i++)
    {
        _cactus[i].init(rand() % 3);
        _cactus[i].setWorldPointer(&_nivel);
        _cactus[i].spawnInMap();
    }

    // Arma inicial
    Weapon* arma = new Weapon();
    _weapons.push_back(arma);
    _weapons[0]->init(0);
    _weapons[0]->setWorldPointer(&_nivel);
    _personaje.setWeapon00(_weapons[0]);


    Chest *cofre;
    for (size_t i = 0; i < 2; i++) // Cofre de munición y arma asegurado en cada mapa
    {
        cofre = new Chest();
        _chest.push_back(*cofre); 
        _chest[i].init(i);
        _chest[i].setWorldPointer(&_nivel);
        _chest[i].setWeaponPointer(&_weapons);
        _chest[i].spawnInMap();
    }

    if (rand() % 10 + 1 - 8 > 0) { // 20% probabilidad de que salga cofre de vida
        cofre = new Chest();
        _chest.push_back(*cofre);
        _chest[_chest.size() - 1].init(2);
        _chest[_chest.size() - 1].setWorldPointer(&_nivel);
        _chest[_chest.size() - 1].setWeaponPointer(&_weapons);
        _chest[_chest.size() - 1].spawnInMap();
    }

    if (rand() % 10 + 1 - 9 > 0) { // 10% probabilidad de que salga cofre de regalo
        cofre = new Chest();
        _chest.push_back(*cofre);
        _chest[_chest.size() - 1].init(3);
        _chest[_chest.size() - 1].setWorldPointer(&_nivel);
        _chest[_chest.size() - 1].setWeaponPointer(&_weapons);
        _chest[_chest.size() - 1].spawnInMap();
    }

    _personaje.spawnInMap();

    Maggot* maggot;
    size = rand() % 10;
    for (size_t i = 0; i < size; i++) // Spawn enemigos
    {
        maggot = new Maggot();
        maggot->init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggot.png"));
        maggot->setWorldPointer(&_nivel);
        maggot->spawnInMap();
        _enemies.push_back(maggot);
    }

    MaggotNest* maggotNest;
    size = rand() % 3;
    for (size_t i = 0; i < size; i++) // Spawn enemigos
    {
        maggotNest = new MaggotNest();
        maggotNest->init();
        maggotNest->setWorldPointer(&_nivel);
        maggotNest->spawnInMap();
        _enemies.push_back(maggotNest);
    }

}

void SceneGame::reinit()
{
    mReinit = false;
}

void SceneGame::update()
{
    //Clear Screen
    sVideo->clearScreen();

    _nivel.update();

    size_t size = _chest.size();
    for (size_t i = 0; i < size; i++)
    {
        _chest[i].update();
    }
    size = _cactus.size();
    for (size_t i = 0; i < size; i++)
    {
        _cactus[i].render();
        if (_cactus[i].getState() != 0) {
            for (size_t j = 0; j < _bullets.size(); j++) // Bullet.size porque el número puede cambiar
            {
                if (_cactus[i].isOverlaping(_bullets[j]->getCollision())) {
                    _cactus[i].receiveDamage();
                    _bullets.erase(_bullets.begin() + j);
                }
            }
        }
    }
    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        _enemies[i]->update();
        if (_enemies[i]->getState() != 0) {
            for (size_t j = 0; j < _bullets.size(); j++) // Bullet.size porque el número puede cambiar
            {
                if (_enemies[i]->isOverlaping(_bullets[j]->getCollision())) {
                    _enemies[i]->receiveDamage(_bullets[j]->getDamage());
                    _bullets.erase(_bullets.begin() + j);
                }
            }
        }
    } 

    for (size_t i = 0; i < _bullets.size(); i++)
    {
        if (_bullets[i]->getX() < 0 - _bullets[i]->getW() ||
            _bullets[i]->getX() > _nivel.getMapWidth() ||
            _bullets[i]->getY() < 0 - _bullets[i]->getW() ||
            _bullets[i]->getY() > _nivel.getMapHeight()) {
            _bullets.erase(_bullets.begin() + i);
            continue;
        }
        _bullets[i]->update();
       
    }
    std::cout << _bullets.size() << std::endl;
    _personaje.update();
    sCamera->update();
    _hud.update();
    sMouse->update();

    if ((sInputControl->getKeyPressed(I_A))) { // 4Debug
        //sDirector->changeScene(GAME_OVER, 1);
        //sHighscore->addScore(1);
    }
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

    size = _weapons.size();
    for (size_t i = 0; i < size; i++)
    {
        _weapons[i]->render(); // Render en el mundo
    }

    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        _enemies[i]->render(); //receive dmg
    }

    _personaje.render();

    size = _bullets.size();
    for (size_t i = 0; i < size; i++)
    {
        _bullets[i]->render();
    }

    _hud.render();
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
