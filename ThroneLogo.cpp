#include "ThroneLogo.h"
#include <time.h> 
#include <stdlib.h>
#include "Video.h"
#include "ResourceManager.h"
#include "KeyDefine.h"

extern Uint32           global_elapsed_time;

ThroneLogo::ThroneLogo()
{
	_Rect.w = 110;
	_Rect.h = 195;
	_Rect.x = WIN_WIDTH / 2 - _Rect.w / 2;
	_Rect.y = WIN_HEIGHT / 2 - _Rect.h / 2;
	_contador = 0;
	_frame = 0;
}

ThroneLogo::~ThroneLogo()
{
}

void ThroneLogo::init(int sprite)
{
	_spriteID = sprite;
	_contador = 0;
	_frame = 0;
}

void ThroneLogo::update()
{
	_contador++;
	if ((_contador * global_elapsed_time) > 120) {
		_frame++;
		if (_frame > 7) {
			_frame = 0;
		}
		_contador = 0;
	}
}

void ThroneLogo::render()
{
	Video::getInstance()->renderGraphic(_spriteID, _Rect.x, _Rect.y, _Rect.w, _Rect.h, _Rect.w * _frame, 0);
}