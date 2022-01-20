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

extern Mouse*           sMouse;
extern SceneDirector*   sDirector;
extern InputManager*    sInputControl;
extern Audio*           sAudio;
extern AudioManager*    sAudioManager;
extern Video*           sVideo;
extern ResourceManager* sResourceManager;

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
}

void SceneSelectCharacter::reinit()
{
}

void SceneSelectCharacter::update()
{
    if ((sInputControl->getKeyPressed(I_A))) {
        sDirector->changeScene(SETTINGS, 1);
    }
}

void SceneSelectCharacter::render()
{
}
