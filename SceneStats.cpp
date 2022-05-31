#include "SceneStats.h"
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

extern Highscore*		sHighscore;
extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneStats::SceneStats()
{
}

SceneStats::~SceneStats()
{
}

void SceneStats::init()
{
	Highscore::getInstance()->resetScore();
	Highscore::getInstance()->readScore();
	Highscore::getInstance()->saveScore();

    mReinit = false;
    _stats.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/stats.png"));

    _SMbutton.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/menuButton.png"), false);
    _SMbutton.setXY(195, 285);
    _SMbutton.setHoldingGraphicRect();

    _SContador = 0;
}

void SceneStats::reinit()
{
	mReinit = false;
    sVideo->setRenderColor(245, 189, 81);

    if (sHighscore->isNewScore()) {
	    sHighscore->readScore();
	    sHighscore->saveScore();
        sHighscore->setNewScore(false);
    }
}

void SceneStats::update()
{
    _SContador += global_elapsed_time;
    sMouse->update();


    _SMbutton.update();

    if ((_SContador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _SMbutton.getIsHoldingBtn())) {
        sDirector->changeScene(MAIN, 1);
    }
}

void SceneStats::render()
{
    sVideo->clearScreen();

    sVideo->renderScreenshot();
    _stats.render();

    _SMbutton.render();

    sHighscore->renderScore();
    sMouse->render();


    sVideo->updateScreen();
}
