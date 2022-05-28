#pragma once
#include "glm/glm.hpp"

class GFXElement
{
protected:
	int _spriteID;

	typedef struct notSDL_Rect
	{
		int x, y;
		int w, h;
	};
	notSDL_Rect _Rect;
public:
	GFXElement();
	~GFXElement();

	virtual void init(int sprite);
	virtual void update();
	virtual void render();

	virtual void moveTo(notSDL_Rect* rect);
	virtual int getType() { return -1; };

	int getX() { return _Rect.x; };
	int getY() { return _Rect.y; };
	void setX(int newX) { _Rect.x = newX; };
	void setY(int newY) { _Rect.y = newY; };
	void setXY(int newX, int newY) { _Rect.x = newX; _Rect.y = newY;};

	int getW() { return _Rect.w; };
	int getH() { return _Rect.h; };

	void setGraphicID(int sprite);
	int getGraphicID();

	int getDistance(notSDL_Rect* otherElement);

	notSDL_Rect* getCollision() { return &_Rect; };
};

