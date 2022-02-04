#include "Timer.h"

Timer::Timer()
{
	_StartTicks = 0;
	_Ticks = 0;
	_Status = 0;
}

Timer::~Timer()
{
}

void Timer::start()
{
	_StartTicks = SDL_GetTicks();
	_Ticks = 0;
	_Status = 1;
}

void Timer::stop()
{
	if (_Status)
	{
		_Status = 0;
		_Ticks += SDL_GetTicks() - _StartTicks;
	}
}

uint32_t Timer::getTicks()
{
	return SDL_GetTicks();
}
