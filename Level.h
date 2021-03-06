#pragma once
#include "GFXElement.h"
#include <string>
#include <vector>

class Level :public GFXElement
{
	notSDL_Rect _RectS;

	std::vector<std::vector<int>> _vBackground;
	std::vector<std::vector<int>> _vForeground;
	std::string _sMapaBg;
	std::string _sMapaFg;
	std::string _string;

	int _w;
	int _h;

	int _len;
	int _tspa;
	int _ID;
	int _cX;
	int _cY;

	int _WW;
	int _WH;

	int _startTileX;
	int _startTileY;
	int _CTW;
	int _CTH;

	int _tileWidth;
	int _tileHeight;
public:
	Level();
	~Level();

	void init();

	void update();
	void render();

	int getTileWidth() {return _tileWidth;};
	int getTileHeight() {return _tileHeight;};
	int getWidth() {return _w;};
	int getHeight() {return _h;};
	int getMapWidth() {return _WW;};
	int getMapHeight() {return _WH;};


	int getIDfromLayer(int layer, int PosX, int PosY);
};

