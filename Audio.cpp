#include "Audio.h"
#include "SDL_mixer.h"
#include "AudioManager.h"

Audio* Audio::pInstance = NULL;

Audio::Audio()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_AllocateChannels(128);
}

Audio::~Audio()
{
}

void Audio::close()
{
	Mix_CloseAudio();
}
void Audio::closeSDL()
{
	SDL_Quit();
}

int Audio::playAudio(int channel, int soundID, int loops)
{
	Mix_Chunk* chunk = AudioManager::getInstance()->getAudioByID(soundID);
	return Mix_PlayChannel(channel, chunk, loops);
}

void Audio::pauseAudio(int channel)
{
	Mix_Pause(channel);
}

void Audio::resumeAudio(int channel)
{
	Mix_Resume(channel);
}

void Audio::stopAudio(int channel)
{
	Mix_HaltChannel(channel);
}

bool Audio::isPlaying(int channel)
{
	return Mix_Playing(channel);
}

Audio* Audio::getInstance()
{
	if (pInstance == NULL) pInstance = new Audio();

	return pInstance;
}