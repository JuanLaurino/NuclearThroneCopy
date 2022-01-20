#include "SceneDirector.h"
#include "SceneMain.h"
#include "SceneSelectCharacter.h"
#include "SceneStats.h"
#include "SceneSettings.h"
#include "SceneInitLevel.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
#include "ScenePause.h"

#include <iostream>

SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance(){
	if (!pInstance) {
		pInstance = new SceneDirector();
	}
	return pInstance;
}

SceneDirector::SceneDirector(){
	init();
}

SceneDirector::~SceneDirector(){
}

void SceneDirector::init(){
	mVectorScenes.resize(NUM_SCENES);

	SceneMain				*main				= new SceneMain();
	SceneSelectCharacter	*SelectCharacter	= new SceneSelectCharacter();
	SceneStats				*Stats				= new SceneStats();
	SceneSettings			*Settings			= new SceneSettings();
	SceneInitLevel			*InitGame			= new SceneInitLevel();
	ScenePause				*Pause				= new ScenePause();
	SceneGame				*game				= new SceneGame();
	SceneGameOver			*gameover			= new SceneGameOver();

	mVectorScenes[MAIN]							= main;
	mVectorScenes[SELECT_CHARACTER]				= SelectCharacter;
	mVectorScenes[STATS]						= Stats;
	mVectorScenes[SETTINGS]						= Settings;
	mVectorScenes[INIT_LEVEL]					= InitGame;
	mVectorScenes[PAUSE]						= Pause;
	mVectorScenes[GAME]							= game;
	mVectorScenes[GAME_OVER]					= gameover;

	main->init();
	SelectCharacter->init();
	Stats->init();
	Settings->init();
	InitGame->init();
	Pause->init();
	game->init();
	gameover->init();

	mCurrScene = MAIN;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit){
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
	std::cout << "Escena: " << next_scene << std::endl;
}
