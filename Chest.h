#pragma once
#include "GFXElementX.h"
class Chest : public GFXElementX
{
	enum CHEST_STATE { ST_IDLE, ST_ANIM, ST_OPENING, ST_OPEN };

	CHEST_STATE _chestState;
	short _type;
	int _wait;

	int _contador;
	int _contadorAnim;
	int _frame;
public:
	Chest();
	~Chest();

	void init(int sprite, int _type);
	void update();
	void render();
	void open();
};

