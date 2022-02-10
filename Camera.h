#pragma once
#include "GFXElement.h"
class Camera :public GFXElement
{
	static Camera* pInstance;
public:
	Camera();
	~Camera();

	void init(int sprite);
	void update();
	void render();

	static Camera* getInstance();
};

