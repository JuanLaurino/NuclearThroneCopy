#pragma once
#include "GFXElement.h"
class Mouse :public GFXElement
{
	static Mouse* pInstance;
public:
	Mouse();
	~Mouse();

	void init();
	void update();
	void render();

	static Mouse* getInstance();
};

