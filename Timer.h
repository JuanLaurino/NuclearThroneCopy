#pragma once
#include "SDL.h"
class Timer
{
	uint32_t _StartTicks;
	uint32_t _Ticks;
	bool _Status;
public:
	Timer();
	~Timer();
	void start();
	void stop();
	uint32_t getTicks(); // uint32_t?
};

