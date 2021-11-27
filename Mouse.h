#pragma once
#include "ElementoGFX.h"
class Mouse :public ElementoGFX
{
	notSDL_Rect mouseCol;
	static Mouse* pInstance;
public:
	Mouse();
	~Mouse();
	void update();
	void render();
	static Mouse* getInstance();
};

