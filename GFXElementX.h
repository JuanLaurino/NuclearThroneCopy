#pragma once
#include "GFXElement.h"
#include "Level.h"

class GFXElementX : public GFXElement
{
public:
	GFXElementX();
	~GFXElementX();

	void render();

	void spawnInMap(Level* pNivel);
};

