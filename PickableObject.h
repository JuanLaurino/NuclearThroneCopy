#pragma once
#include "GFXElement.h"
#include "Character.h"

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
	int _rotation;
public:
	PickableObject();
	~PickableObject();

	void init(int type, int posX, int posY);
	void update();
	void render();

	void moveTo(notSDL_Rect* rect);
	int getType() { return _type; };
};

