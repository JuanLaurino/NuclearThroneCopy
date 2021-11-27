#pragma once

#include <map>
#include <vector>
#include <string>
#include "SDL_mixer.h"

/*
	Handles the load and management of the audio in the game.
*/
class AudioManager
{
	AudioManager();

	static AudioManager* pInstance;

	int addAudio(const char* file);
	Uint32 updateFirstFreeSlotAudio();

	std::vector<Mix_Chunk*>			_AudioVector;
	std::map<std::string, Sint32>	_IDMap;
	Uint32							_FirstFreeSlot;
public:
	~AudioManager();

	void removeAudio(const char* file);
	std::string getAudioPathByID(Sint32 ID);
	Mix_Chunk* getAudioByID(Sint32 ID);
	int loadAndGetAudioID(const char* file);

	static AudioManager* getInstance();
};
