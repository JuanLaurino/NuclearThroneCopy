#include "SceneDirector.h"
#include "InputManager.h"
#include "Audio.h"
#include "AudioManager.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Mouse.h"
#include "Camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "Highscore.h"

Uint32 				global_elapsed_time = 0;
bool				gameOn = true;
int					characterPicked = -1;

SceneDirector*		sDirector = NULL;
InputManager*		sInputControl = NULL;
Video*				sVideo = NULL;
ResourceManager*	sResourceManager = NULL;
Audio*				sAudio = NULL;
AudioManager*		sAudioManager = NULL;
Mouse*				sMouse = NULL;
Camera*				sCamera = NULL;
Highscore*			sHighscore = NULL;


int main( int argc, char* argv[] ) { 
	srand(time(NULL));
	//Init Singletons en orden
	sCamera				= Camera::getInstance();
	sResourceManager	= ResourceManager::getInstance();
	sVideo				= Video::getInstance();
	sAudioManager		= AudioManager::getInstance();
	sAudio				= Audio::getInstance();
	sInputControl		= InputManager::getInstance();
	sMouse				= Mouse::getInstance();
	sDirector			= SceneDirector::getInstance();
	sHighscore			= Highscore::getInstance();


	//Main Loop
	// Init Time control
	Timer* globalTimer = new Timer();
	globalTimer->start();
	Uint32 last_time = 0;

	while (gameOn){
		//ReInit o no
		if(sDirector->getCurrentScene()->mustReInit()){
			sDirector->getCurrentScene()->reinit();
		}
		// Read controls
		sInputControl->update();
		
		//Update time
		Uint32 actualtime = globalTimer->getTicks();
		global_elapsed_time = actualtime - last_time;
		last_time =  actualtime;
		
		// Updates scene
		sDirector->getCurrentScene()->update();

		if(!sDirector->getCurrentScene()->mustReInit()){
			sDirector->getCurrentScene()->render();
		}
	}

	sVideo->close();
	sAudio->close();
	sVideo->closeSDL();
	return 0;
}

