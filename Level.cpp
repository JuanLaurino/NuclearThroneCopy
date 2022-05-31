#include "Level.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include "Video.h"
#include "ResourceManager.h"
#include "SceneDirector.h"
#include "Camera.h"
#include "KeyDefine.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Camera* sCamera;

Level::Level()
{
	_tileWidth = 0;
	_tileHeight = 0;
	_RectS.h = 0;
	_RectS.w = 0;
	_RectS.x = 0;
	_RectS.y = 0;
	_Rect.h = 0;
	_Rect.w = 0;
	_Rect.x = 0;
	_Rect.y = 0;

	_vBackground.resize(0);
	_vForeground.resize(0);

	_sMapaBg = "";
	_sMapaFg = "";

	_string = "";

	_w = 0;
	_h = 0;
	_ID = 0;
	_cX = 0;
	_cY = 0;
	_tspa = 0;

	_WW = 0;
	_WH = 0;
	_startTileX = 0;
	_startTileY = 0;
	_CTW = 0;
	_CTH = 0;
}

Level::~Level()
{
}

void Level::init()
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/LevelSprites/tileset_level.png");

	tinyxml2::XMLDocument mapa;
	if (mapa.LoadFile(("Assets/Levels/level0" + std::to_string(rand() % 7) + ".tmx").c_str()) != tinyxml2::XML_SUCCESS) {
		std::cout << "Error XML: " << mapa.ErrorStr();
		exit(1);
	}


	tinyxml2::XMLElement* root = mapa.FirstChildElement();
	tinyxml2::XMLElement* tileset = root->FirstChildElement();
	tinyxml2::XMLElement* backgroundLayer = tileset->NextSiblingElement();
	//tinyxml2::XMLElement* foregroundLayer = backgroundLayer->NextSiblingElement();
	tinyxml2::XMLElement* XMLBackground = backgroundLayer->FirstChildElement();
	//tinyxml2::XMLElement* XMLForeground = foregroundLayer->FirstChildElement();

	_w = std::stoi(backgroundLayer->Attribute("width"));
	_h = std::stoi(backgroundLayer->Attribute("height"));

	_sMapaBg = XMLBackground->GetText();
	//_sMapaFg = XMLForeground->GetText();

	_vBackground.resize(_h);
	//_vForeground.resize(_h);
	for (size_t i = 0; i < (size_t)_h; i++) {
		_vBackground.at(i).resize(_w);
		//_vForeground.at(i).resize(_w);
	}

	for (size_t i = 0; i < (size_t)_h; i++)
	{
		for (size_t j = 0; j < (size_t)_w; j++)
		{
			// Background
			_len = _sMapaBg.find_first_of(',');
			_string = _sMapaBg.substr(0, _len);
			_sMapaBg = _sMapaBg.substr(_len + 1);
			_vBackground.at(i).at(j) = std::stoi(_string);

			//Foreground
			/*
			_len = _sMapaFg.find_first_of(',');
			_string = _sMapaFg.substr(0, _len);
			_sMapaFg = _sMapaFg.substr(_len + 1);
			_vForeground.at(i).at(j) = std::stoi(_string);
			*/
		}
	}
	_tileWidth = std::stoi(tileset->Attribute("tilewidth"));
	_tileHeight = std::stoi(tileset->Attribute("tileheight"));
	_tspa = std::stoi(tileset->Attribute("spacing"));

	_WW = _w * _tileWidth;
	_WH = _h * _tileHeight;
}

void Level::update()
{
	_startTileX = sCamera->getX() / _tileWidth;
	_startTileY = sCamera->getY() / _tileHeight;
	_CTW = (WIN_WIDTH / _tileWidth) + _startTileX + 1;
	_CTH = (WIN_HEIGHT / _tileHeight) + _startTileY + 1;

	if (_CTW > 30) {
		_CTW = 30;
	}
	if (_CTH > 30) {
		_CTH = 30;
	}
}

void Level::render()
{
	for (int fy = _startTileY; fy < _CTH; fy++)
	{
		for (int fx = _startTileX; fx < _CTW; fx++)
		{
			//Background
			_Rect.x = (fx * _tileWidth) - sCamera->getX();
			_Rect.y = (fy * _tileHeight) - sCamera->getY();
			_ID = _vBackground.at(fy).at(fx) - 1;

			if (_ID >= 0) {
				_cX = _ID % 4; 
				_cY = _ID / 4; 

				_RectS.x = _cX * _tileWidth + _tspa * _cX;
				_RectS.y = _cY * _tileHeight + _tspa * _cY;
				_RectS.w = _tileWidth;
				_RectS.h = _tileHeight;

				sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _RectS.w, _RectS.h, _RectS.x, _RectS.y);
			}

			//Foreground
			/*
			_Rect.x = (fx * _tileWidth) - sCamera->getX();
			_Rect.y = (fy * _tileHeight) - sCamera->getY();
			_ID = _vForeground.at(fy).at(fx) - 1;

			if (_ID >= 0) {
				_cX = _ID % 15; 
				_cY = _ID / 15; 

				_RectS.x = _cX * _tileWidth + _tspa * _cX;
				_RectS.y = _cY * _tileHeight + _tspa * _cY;
				_RectS.w = _tileWidth;
				_RectS.h = _tileHeight;

				sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _RectS.w, _RectS.h, _RectS.x, _RectS.y);
			}
			*/
		}
	}
}

int Level::getIDfromLayer(int layer, int PosX, int PosY)
{
	if (PosX >= 1200) {
		PosX = 1199;
	}
	if (PosY >= 1200) {
		PosY = 1199;
	}
	// LAYER
	int TileX = PosX / _tileWidth;
	int TileY = PosY / _tileHeight;
	return _vBackground[TileY][TileX];
}
