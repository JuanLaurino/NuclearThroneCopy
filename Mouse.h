#pragma once
#include "ElementoGFX.h"
class Mouse :public ElementoGFX
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

