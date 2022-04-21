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
	_Rect.w = 16;
	_Rect.h = 16;
}

