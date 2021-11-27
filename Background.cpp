#include "Background.h"
#include "ResourceManager.h"
#include "Video.h"
#include <string>
#include "Main.h"
#include <iostream>
extern Uint32 global_elapsed_time;

Background::Background()
{
	_spriteID = 0;
	_contador = 0;
	_frame = 0;
	for (size_t i = 0; i < 97; i++)
	{
		_bSpriteID[i] = 0;
	}
}

Background::~Background()
{
}

void Background::init()
{
	_frame = 0;
	for (size_t i = 0; i < 97; i++)
	{
		if (i < 10) {
			_bSpriteID[i] = ResourceManager::getInstance()->loadAndGetGraphicID(Video::getInstance()->getRenderer(), ("Assets/background/background_00" + std::to_string(i) + ".jpg").c_str()); // Convierto de string a const char*
		}
		else {
			_bSpriteID[i] = ResourceManager::getInstance()->loadAndGetGraphicID(Video::getInstance()->getRenderer(), ("Assets/background/background_0" + std::to_string(i) + ".jpg").c_str());
		}
	}
	_spriteID = _bSpriteID[0];
	ResourceManager::getInstance()->getGraphicSize(_spriteID, &_Rect.w, &_Rect.h);
	_Rect.y = (WIN_HEIGHT - _Rect.h) / 2;
}

void Background::update()
{
	_spriteID = _bSpriteID[_frame];
	_contador++;
	if (_contador * global_elapsed_time >= 40) {
		_frame++;
		if (_frame == 97) {
			_frame = 0;
		}
		_contador = 0;
	}

}