#pragma once

#include "sdl.h"

class Audio
{
	static Audio* pInstance;
	Audio();
public:
	~Audio();
	void close();
	void closeSDL();
	int playAudio(int channel, int chunk, int loops);
	void pauseAudio(int channel);
	void resumeAudio(int channel);
	void stopAudio(int channel);
	bool isPlaying(int channel);
	static Audio* getInstance();
};