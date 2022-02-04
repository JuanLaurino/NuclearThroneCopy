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

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

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
}

void SceneGame::reinit()
{
}

void SceneGame::update()
{
    //Clear Screen
    sVideo->clearScreen();

    //if ((sInputControl->getKeyPressed(I_A))) {
    //    sDirector->changeScene(GAME_OVER, 1);
    //}
}

void SceneGame::render()
{
    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
