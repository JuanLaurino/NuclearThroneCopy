#include "AudioManager.h"
#include <iostream>

AudioManager* AudioManager::pInstance = NULL;

AudioManager::AudioManager()
{
	_FirstFreeSlot = 0;
}

AudioManager::~AudioManager()
{
}

void AudioManager::removeAudio(const char* file)
{
	_AudioVector[_IDMap.find(file)->second] = NULL;
	_IDMap.erase(file);
}

std::string AudioManager::getAudioPathByID(Sint32 ID)
{
	for (const auto& it : _IDMap) // Look at each key-value pair
	{
		if (it.second == ID) // If value is ID
		{
			return it.first; // Return the first element in the pair
		}
	}
	return "ERROR: Graphic not found";
}


Mix_Chunk* AudioManager::getAudioByID(Sint32 ID)
{
	return _AudioVector.at(ID);
}


int AudioManager::loadAndGetAudioID(const char* file)
{
	if (_IDMap.find(file) == _IDMap.end()) { return addAudio(file); }; //Creates a new audio and returns the ID

	return _IDMap.find(file)->second; //Returns the ID of the audio
}

int AudioManager::addAudio(const char* file)
{
	_FirstFreeSlot = updateFirstFreeSlotAudio();

	Mix_Chunk* audio = Mix_LoadWAV(file);
	if (!audio) {
		std::cout << "ERROR, AUDIO \"" << file << "\" NO ENCONTRADO" << std::endl;
		std::cout << Mix_GetError() << std::endl;
		system("pause");
		return -1;
	}
	if (!(_FirstFreeSlot == -1)) { //Si hay espacio libre (No es -1)
		_AudioVector[_FirstFreeSlot] = audio;
		_IDMap.insert(std::pair<std::string, int>(file, _FirstFreeSlot));
	}
	else { //Si no hay espacio libre
		_AudioVector.push_back(audio);
		_IDMap.insert(std::pair<std::string, int>(file, _AudioVector.size() - 1));
	}

	return _IDMap.find(file)->second;
}

Uint32 AudioManager::updateFirstFreeSlotAudio()
{
	for (size_t i = 0; i < _AudioVector.size(); i++)
	{
		if (_AudioVector[i] == NULL) {
			return i;
		}
	}

	return -1;
}

AudioManager* AudioManager::getInstance()
{
	if (pInstance == NULL)pInstance = new AudioManager();
	return pInstance;
}