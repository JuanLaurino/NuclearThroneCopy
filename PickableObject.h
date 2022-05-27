#pragma once
#include "GFXElement.h"
class PickableObject : public GFXElement
{
	enum OBJECT_STATE { ST_IDLE, ST_ANIM};

	OBJECT_STATE _objState;
	notSDL_Rect _rectFrame;

	int _type;
	int _wait;

	int _contador;
	int _contadorAnim;
	int _frame;
public:
	PickableObject();
	~PickableObject();

	void init(int type, int posX, int posY);
	void update();
	void render();

	int getType() { return _type; };
};

