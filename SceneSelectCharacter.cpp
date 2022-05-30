#include "SceneSelectCharacter.h"
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

#include <iostream>
extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

extern int				characterPicked;
extern bool             gameOn;
extern Uint32           global_elapsed_time;

SceneSelectCharacter::SceneSelectCharacter()
{
}

SceneSelectCharacter::~SceneSelectCharacter()
{
}

void SceneSelectCharacter::init()
{
    mReinit = false;

    _SCcontador = 0;

    _selectCharacterIMG.init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/selectCharacter.png"));

    _SCbutton[0].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/backButton.png"), false);
    _SCbutton[0].setXY(0, 5);
    _SCbutton[0].setHoldingGraphicRect();

    _SCbutton[1].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/randomButton.png"), false);
    _SCbutton[1].setXY(12, 314);
    _SCbutton[1].setHoldingGraphicRect();

    _SCbutton[2].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/fishButton.png"), false);
    _SCbutton[2].setXY(44, 314);
    _SCbutton[2].setHoldingGraphicRect();

    _SCbutton[3].init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/menu/steroidsButton.png"), false);
    _SCbutton[3].setXY(74, 314);
    _SCbutton[3].setHoldingGraphicRect();

}

void SceneSelectCharacter::reinit()
{
    mReinit = false;
    sVideo->setRenderColor(245, 189, 81);
}

void SceneSelectCharacter::update()
{
    //Clear Screen
    sVideo->clearScreen();

    _SCcontador += global_elapsed_time;

    for (size_t i = 0; i <= 3; i++)
    {
        _SCbutton[i].update();
    }

    if ((_SCcontador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _SCbutton[0].getIsHoldingBtn())) { //Si le da a PLAY
        sDirector->changeScene(MAIN, 1);
    }
    if ((_SCcontador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _SCbutton[1].getIsHoldingBtn())) { //Si le da a PLAY
        characterPicked = rand() % 2;
        sDirector->getScene(GAME)->reset();
        sDirector->changeScene(GAME, 1);
    }
    if ((_SCcontador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _SCbutton[2].getIsHoldingBtn())) { //Si le da a PLAY
        characterPicked = 0;
        sDirector->getScene(GAME)->reset();
        sDirector->changeScene(GAME, 1);
    }
    if ((_SCcontador > 400) && (sInputControl->getKeyPressed(I_CLICK) && _SCbutton[3].getIsHoldingBtn())) { //Si le da a PLAY
        characterPicked = 1;
        sDirector->getScene(GAME)->reset();
        sDirector->changeScene(GAME, 1);
    }

    sMouse->update();

}

void SceneSelectCharacter::render()
{
    sVideo->clearScreen();

    _selectCharacterIMG.render();

    for (size_t i = 0; i <= 3; i++)
    {
        _SCbutton[i].render();
    }


    sMouse->render();

    //Update Screen
    sVideo->updateScreen();
}
