#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <vector>
#include "Scene.h"

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum {
		MAIN, SELECT_CHARACTER, STATS, SETTINGS, INIT_LEVEL, GAME_OVER, GAME, PAUSE,
		_LASTSCENE};

#define NUM_SCENES _LASTSCENE

class SceneDirector
{
	public:
		~SceneDirector();

		void init();
		
		void changeScene(SceneEnum next_scene, bool reinit = true);

		SceneEnum getCurrSceneEnum(){return mCurrScene;};

		Scene* getCurrentScene(){return mVectorScenes[mCurrScene];};
		
		//! Gets pointer to instance
		static SceneDirector* getInstance();

	protected:
		SceneDirector();
		static SceneDirector*	pInstance;	/*!<  pointer instance*/

		std::vector<Scene*>	mVectorScenes;
		SceneEnum		mCurrScene;
};

#endif
