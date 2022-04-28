#pragma once
#include "GFXElement.h"
#include "Level.h"

class GFXElementX : public GFXElement
{
protected:
	notSDL_Rect _rectFrame;
public:
	GFXElementX();
	~GFXElementX();

	void render();

	void spawnInMap(Level* pNivel);
	bool isOverlaping(notSDL_Rect* obj01);
};

