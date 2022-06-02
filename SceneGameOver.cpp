#include "SceneGameOver.h"
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
#include "Highscore.h"

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;
extern Highscore*       sHighscore;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::init()
{
    mReinit = false;
    _gameOver.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/gameOver.png"));

    _GObutton[0].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/menuButton.png"), false);
    _GObutton[0].setXY(195, 285);
    _GObutton[0].setHoldingGraphicRect();

    _GObutton[1].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/retryButton.png"), false);
    _GObutton[1].setXY(196, 315);
    _GObutton[1].setHoldingGraphicRect();

    _goContador = 0;
}

void SceneGameOver::reinit()
{
    mReinit = false;
    sVideo->setRenderColor(245, 189, 81);

    Audio::getInstance()->playAudio(-1, sAudioManager->loadAndGetAudioID("Assets/sound/CuzCry.ogg"), 0);
}

void SceneGameOver::update()
{
    _goContador += global_elapsed_time;
    sMouse->update();

    for (size_t i = 0; i < 2; i++)
    {
        _GObutton[i].update();
    }

    if ((_goContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _GObutton[0].getIsHoldingBtn())) {
        sDirector->changeScene(MAIN, 1);
    }
    if ((_goContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _GObutton[1].getIsHoldingBtn())) {
        sDirector->getScene(GAME)->reset();
        sDirector->changeScene(GAME, 1);
    }


    sHighscore->setNewScore(true);
}

void SceneGameOver::render()
{
    sVideo->clearScreen();

    sVideo->renderScreenshot();
    _gameOver.render();

    for (size_t i = 0; i < 2; i++)
    {
        _GObutton[i].render();
    }

    sMouse->render();


    sVideo->updateScreen();
}
