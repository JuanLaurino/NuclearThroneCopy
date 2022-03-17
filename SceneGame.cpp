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
}

void SceneGame::reinit()
{
    mReinit = false;
}

void SceneGame::update()
{
    //Clear Screen
    sVideo->clearScreen();

    //
    _nivel.update();
    _personaje.update();
    sCamera->update();
    sMouse->update();

    //if ((sInputControl->getKeyPressed(I_A))) {
    //    sDirector->changeScene(GAME_OVER, 1);
    //}
}

void SceneGame::render()
{
    sMouse->render();
    _nivel.render();
    _personaje.render();
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
