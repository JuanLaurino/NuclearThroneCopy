#include "SceneGame.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "Audio.h"
#include "Video.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Background.h"
#include "KeyDefine.h"
#include "SceneMain.h"
#include "SceneDirector.h"
#include "Camera.h"
#include <iostream>
#include "MaggotNest.h"
#include "Highscore.h"
#include "Bandit.h"
#include "PickableObject.h"
#include "Canister.h"
#include "BigMaggot.h"
#include "Scorpion.h"
#include "Steroids.h"

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;
extern Camera*          sCamera;
extern Highscore*       sHighscore;

extern int              characterPicked;
extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneGame::SceneGame()
{
    _chest.resize(0);
    _enemies.resize(0);
    _bullets.resize(0);
    _weapons.resize(0);
    _cactus.resize(0);
    _pickableObjects.resize(0);

    _changeLevel = false;
    _changeLevelTimer = 600;
    _dificultad = 0;
}

SceneGame::~SceneGame()
{
}

void SceneGame::init()
{
    Highscore::getInstance()->init();
    _takeSS = false;
}

void SceneGame::reinit()
{
    sVideo->setRenderColor(245, 189, 81);

    Audio::getInstance()->playAudio(-1, sAudioManager->loadAndGetAudioID("Assets/sound/Mutant1Spch.ogg"), 0);
    if (_personaje == nullptr) {
        _portal.init();
        if (characterPicked == 0) {
            Fish* fish;
            fish = new Fish();
            _personaje = fish;
        }
        else {
            Steroids* steroids;
            steroids = new Steroids();
            _personaje = steroids;
        }
        deletePointers();

        mReinit = false;

        _changeLevel = false;
        _changeLevelTimer = 3500;
        _dificultad = 1;
        _nivel.init();

        _personaje->init();
        _personaje->setWorldPointer(&_nivel);
        _personaje->setBulletsPointer(&_bullets);
        _personaje->setWeaponPointer(&_weapons);
        _personaje->setChestPointer(&_chest);
        _personaje->setEnemiesPointer(&_enemies);
        _personaje->setObjectPointer(&_pickableObjects);

        // Arma inicial
        Weapon* arma = new Weapon();
        _weapons.push_back(arma);
        _weapons[0]->init(0);
        _weapons[0]->setWorldPointer(&_nivel);
        _personaje->setWeapon00(_weapons[0]);

        _hud.setPlayerPointer(_personaje);
        _hud.init();

        sCamera->init(_personaje, &_nivel);
        spawnActorsInMap();

        _personaje->setImmunity(true);
        _justSpawned = true;
        _timer = 0;
    }
    else {
        _personaje->setImmunity(true);
        mReinit = false;
        _changeLevel = false;
        _changeLevelTimer = 3500;
        _dificultad++;

        _justSpawned = true;
        _timer = 0;
        _nivel.init();

        if (_personaje->getInventoryWeapon1() != NULL) { // Dejando solo las dos armas que tiene el jugador
            _weapons.resize(2);
            _weapons.at(0) = _personaje->getInventoryWeapon0();
            _weapons.at(1) = _personaje->getInventoryWeapon1();
        }
        else {
            _weapons.resize(1);
            _weapons.at(0) = _personaje->getInventoryWeapon0();
        }

        spawnActorsInMap();
    }
}

void SceneGame::update()
{
    if (_justSpawned) {
        _timer += global_elapsed_time;
        if (_timer >= 3000) {
            _personaje->setImmunity(false);
            _justSpawned = false;
            _doOnce = true;
        }
        else if (_timer >= 500) {
            if (_doOnce) {
                _doOnce = false;
                _personaje->setState(0);
            }
        }
    }

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
                // if from player
                if (_bullets[j]->getCollCounter() == -2) {
                    if (_cactus[i].isOverlaping(_bullets[j]->getCollision())) {
                        _cactus[i].receiveDamage();
                        _bullets[j]->setCollided();
                        break;
                    }
                }
            }
        }
    }
    size_t deadEnemies = 0;
    size = _enemies.size();
    if (size == 1) {
        _portal.setX(_enemies[0]->getX());
        _portal.setY(_enemies[0]->getY());
    }
    for (size_t i = 0; i < size; i++)
    {
        _enemies[i]->update();
        if (_enemies[i]->getState() != 0) {
            for (size_t j = 0; j < _bullets.size(); j++) // Bullet.size porque el número puede cambiar
            {
                if (_bullets[j]->getCollCounter() == -2) {
                    if (_enemies[i]->isOverlaping(_bullets[j]->getCollision())) {
                        _enemies[i]->receiveDamageFromBullet(_bullets[j]->getDamage(), _bullets[j]->getSpeedX(), _bullets[j]->getSpeedY(), _personaje->getDistance(_enemies[i]->getCollision()));
                        _bullets[j]->setCollided();
                        break;
                    }
                }
            }
        }
        else {
            deadEnemies++;
        }
    } 
    if (size == deadEnemies) {
        _changeLevel = true;
    }

    for (size_t i = 0; i < _bullets.size(); i++)
    {
        if (_bullets[i]->getCollCounter() >= 640) {
            delete _bullets[i];
            _bullets.erase(_bullets.begin() + i);
            continue;
        }

        _bullets[i]->update();

        if (_bullets[i]->getX() < 0 - _bullets[i]->getW() ||
            _bullets[i]->getX() > _nivel.getMapWidth() ||
            _bullets[i]->getY() < 0 - _bullets[i]->getW() ||
            _bullets[i]->getY() > _nivel.getMapHeight()) {
            _bullets[i]->setCollided();
            continue;
        }

        if (_nivel.getIDfromLayer(0, _bullets[i]->getX(), _bullets[i]->getY())) {
            _bullets[i]->setCollided();
            continue;
        }
        if (_nivel.getIDfromLayer(0, _bullets[i]->getX() + _bullets[i]->getW(), _bullets[i]->getY())) {
            _bullets[i]->setCollided();
            continue;
        }
        if (_nivel.getIDfromLayer(0, _bullets[i]->getX(), _bullets[i]->getY() + _bullets[i]->getH())) {
            _bullets[i]->setCollided();
            continue;
        }
        if (_nivel.getIDfromLayer(0, _bullets[i]->getX() + _bullets[i]->getW(), _bullets[i]->getY() + _bullets[i]->getH())) {
            _bullets[i]->setCollided();
            continue;
        }
        
        if (!_bullets[i]->isBulletFromPlayer()) {// bullet collision with player
            if (_bullets[i]->getCollCounter() == -1) { 
                if (_personaje->isOverlaping(_bullets[i]->getCollision())) {
                    _personaje->receiveDamage(_bullets[i]->getDamage());
                    _bullets[i]->setCollided();
                    break;
                }
            }
        }
    }
    size = _pickableObjects.size();
    for (size_t i = 0; i < size; i++)
    {
        _pickableObjects[i]->update();
        if (_changeLevel && _personaje->getHP() > 0) {
            _pickableObjects[i]->moveTo(_personaje->getCollision());
        }
    }    

    _personaje->update();
    sCamera->update();
    _hud.update();
    sMouse->update();

    if (_personaje->getHP() <= 0) {
        _changeLevel = true;
    }
    if (_changeLevel && _personaje->getHP() > 0) {
        _personaje->setState(3);
        sCamera->shake();

        _portal.update();

        _changeLevelTimer -= global_elapsed_time;
        if (_changeLevelTimer <= 0) {

            sDirector->changeScene(GAME, 1);
            deletePointers();
        }
    }
    else if (_changeLevel && _personaje->getHP() <= 0) {
        _changeLevelTimer -= global_elapsed_time;
        if (_changeLevelTimer <= 0) {
            _takeSS = true;
            render(); // Para sacar captura
            deletePointers();
            //sDirector->changeScene(STATS, 1);
            sDirector->changeScene(GAME_OVER, 1);
        }
    }

    if (sInputControl->getKeyPressed(I_P)) {
        _takeSS = true;
        render(); // Para sacar captura
        sDirector->changeScene(PAUSE, 1);
    }
}

void SceneGame::render()
{

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

    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        if (_enemies[i]->getState() == 0) {
            _enemies[i]->render();
        }
    }

    size = _weapons.size();
    for (size_t i = 0; i < size; i++)
    {
        _weapons[i]->render(); // Render en el mundo
    }

    size = _pickableObjects.size();
    for (size_t i = 0; i < size; i++)
    {
        _pickableObjects[i]->render();
    }

    size = _enemies.size();
    for (size_t i = 0; i < size; i++)
    {
        if (_enemies[i]->getState() != 0) {
            _enemies[i]->render();
        }
    }

    _personaje->render();

    size = _bullets.size();
    for (size_t i = 0; i < size; i++)
    {
        _bullets[i]->render();
    }

    if (_changeLevel && _personaje->getHP() > 0) {
        _portal.render();
    }

    if (!(_changeLevel && _changeLevelTimer <= 0)) {
        _hud.render();
        sMouse->render();
    }

    //Update Screen
    sVideo->updateScreen();

    if (_takeSS) {
        sVideo->takeScreenshot();
        _takeSS = false;
    }
}

void SceneGame::spawnActorsInMap()
{
    _cactus.resize(rand() % 7);
    size_t size = _cactus.size();
    for (size_t i = 0; i < size; i++) // Spawn cactus
    {
        _cactus[i].init(rand() % 3);
        _cactus[i].setWorldPointer(&_nivel);
        _cactus[i].spawnInMap();
    }

    Chest* cofre;
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

    _personaje->spawnInMap();

    Maggot* maggot;
    size = rand() % 7 + _dificultad + 4;
    for (size_t i = 0; i < size; i++) // Spawn Maggots
    {
        maggot = new Maggot();
        maggot->init(0);
        maggot->setWorldPointer(&_nivel);
        maggot->spawnInMap();
        maggot->setObjectPointer(&_pickableObjects);
        _enemies.push_back(maggot);
    }

    MaggotNest* maggotNest;
    size = rand() % _dificultad;
    for (size_t i = 0; i < size; i++) // Spawn MaggotNest
    {
        maggotNest = new MaggotNest();
        maggotNest->init();
        maggotNest->setWorldPointer(&_nivel);
        maggotNest->setEnemiesPointer(&_enemies);
        maggotNest->spawnInMap();
        maggotNest->setObjectPointer(&_pickableObjects);
        _enemies.push_back(maggotNest);
    }

    Bandit* bandit;
    size = rand() % 4 + _dificultad;
    for (size_t i = 0; i < size; i++) // Spawn Bandits
    {
        bandit = new Bandit();
        bandit->init();
        bandit->setWorldPointer(&_nivel);
        bandit->setPlayerPointer(_personaje);
        bandit->setBulletsPointer(&_bullets);
        bandit->spawnInMap();
        bandit->setObjectPointer(&_pickableObjects);
        _enemies.push_back(bandit);
    }

    BigMaggot* bigMaggot;
    size = rand() % _dificultad;
    for (size_t i = 0; i < size; i++) // Spawn BigMaggots
    {
        bigMaggot = new BigMaggot();
        bigMaggot->init();
        bigMaggot->setWorldPointer(&_nivel);
        bigMaggot->setEnemiesPointer(&_enemies);
        bigMaggot->setPlayerPointer(_personaje);
        bigMaggot->spawnInMap();
        bigMaggot->setObjectPointer(&_pickableObjects);
        _enemies.push_back(bigMaggot);
    }

    Scorpion* scorpion;
    size = rand() % _dificultad;
    for (size_t i = 0; i < size; i++) // Spawn Scorpions
    {
        scorpion = new Scorpion();
        scorpion->init();
        scorpion->setWorldPointer(&_nivel);
        scorpion->setPlayerPointer(_personaje);
        scorpion->spawnInMap();
        scorpion->setObjectPointer(&_pickableObjects);
        scorpion->setBulletsPointer(&_bullets);
        _enemies.push_back(scorpion);
    }

    Canister* canister;
    canister = new Canister(); // Spawn Canister
    canister->init();
    canister->setWorldPointer(&_nivel);
    canister->spawnInMap();
    canister->setObjectPointer(&_pickableObjects);
    canister->setEnemiesPointer(&_enemies);
    _enemies.push_back(canister);
}

void SceneGame::deletePointers()
{
    _cactus.resize(0);
    _chest.resize(0);

    size_t size = _enemies.size();
    for (size_t i = 0; i < size; i++) // Spawn enemigos
    {
        delete _enemies[i];
    }
    _enemies.resize(0);

    for (size_t i = 0; i < _weapons.size(); i++)
    {
        if (!(_weapons[i] == _personaje->getInventoryWeapon0() || _weapons[i] == _personaje->getInventoryWeapon1())) {
            delete _weapons[i];
            _weapons.erase(_weapons.begin() + i);
        }
    }

    size = _pickableObjects.size();
    for (size_t i = 0; i < size; i++)
    {
        delete _pickableObjects[i];
    }
    _pickableObjects.resize(0);
}

void SceneGame::reset()
{
    delete _personaje;
    _personaje = nullptr;

    for (size_t i = 0; i < _weapons.size(); i++)
    {
        delete _weapons[i];
    }
    _weapons.resize(0);

    _dificultad = 0;

    sHighscore->resetScore();
}
