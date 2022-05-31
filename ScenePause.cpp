#include "ScenePause.h"
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

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

ScenePause::ScenePause()
{
}

ScenePause::~ScenePause()
{
}


void ScenePause::init()
{
    mReinit = false;
    _pause.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/pause.png"));

    _Pbutton[0].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/menuButton.png"), false);
    _Pbutton[0].setXY(195, 285);
    _Pbutton[0].setHoldingGraphicRect();

    _Pbutton[1].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/retryButton.png"), false);
    _Pbutton[1].setXY(196, 315);
    _Pbutton[1].setHoldingGraphicRect();

    _Pbutton[2].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/continueButton.png"), false);
    _Pbutton[2].setXY(15, 315);
    _Pbutton[2].setHoldingGraphicRect();

    _pContador = 0;
}

void ScenePause::reinit()
{
    mReinit = false;
    sVideo->setRenderColor(0, 0, 0);
}

void ScenePause::update()
{
    _pContador += global_elapsed_time;
    sMouse->update();

    for (size_t i = 0; i < 3; i++)
    {
        _Pbutton[i].update();
    }

    if ((_pContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _Pbutton[0].getIsHoldingBtn())) {
        sDirector->changeScene(MAIN, 1);
    }
    if ((_pContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _Pbutton[1].getIsHoldingBtn())) {
        sDirector->getScene(GAME)->reset();
        sDirector->changeScene(GAME, 1);
    }
    if ((_pContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _Pbutton[2].getIsHoldingBtn())) {
        sVideo->setRenderColor(245, 189, 81);
        sDirector->changeScene(GAME, 0);
    }
}

void ScenePause::render()
{
    sVideo->clearScreen();

    sVideo->renderScreenshot();
    _pause.render();

    for (size_t i = 0; i < 3; i++)
    {
        _Pbutton[i].render();
    }

    sMouse->render();


    sVideo->updateScreen();
}
