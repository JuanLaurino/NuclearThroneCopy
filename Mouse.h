#pragma once
#include "GFXElement.h"
class Mouse :public GFXElement
{
	static Mouse* pInstance;
public:
	Mouse();
	~Mouse();

	void init(int sprite);
	void update();
	void render();

	static Mouse* getInstance();
};

