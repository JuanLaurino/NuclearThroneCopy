#include "Maggot.h"

Maggot::Maggot()
{
}

Maggot::~Maggot()
{
}

void Maggot::init(int sprite)
{
	_spriteID = sprite;
	_rectFrame.w = 16;
	_rectFrame.h = 16;
	_Rect.w = 16;
	_Rect.h = 16;
}

