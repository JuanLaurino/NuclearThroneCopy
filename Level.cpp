#include "Level.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include "Video.h"
#include "ResourceManager.h"
#include "SceneDirector.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;

Level::Level()
{
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
}

Level::~Level()
{
}

void Level::init(const char* XMLMap, int sprite)
{
	_spriteID = sprite;
	tinyxml2::XMLDocument mapa;
	if (mapa.LoadFile(XMLMap) != tinyxml2::XML_SUCCESS) {
		std::cout << "Error XML: " << mapa.ErrorStr();
		exit(1);
	}

	tinyxml2::XMLElement* root = mapa.FirstChildElement();
	tinyxml2::XMLElement* tileset = root->FirstChildElement();
	tinyxml2::XMLElement* imagelayer = tileset->NextSiblingElement();
	tinyxml2::XMLElement* backgroundLayer = imagelayer->NextSiblingElement();
	tinyxml2::XMLElement* foregroundLayer = backgroundLayer->NextSiblingElement();
	tinyxml2::XMLElement* XMLBackground = backgroundLayer->FirstChildElement();
	tinyxml2::XMLElement* XMLForeground = foregroundLayer->FirstChildElement();

	_w = std::stoi(backgroundLayer->Attribute("width"));
	_h = std::stoi(backgroundLayer->Attribute("height"));

	_sMapaBg = XMLBackground->GetText();
	_sMapaFg = XMLForeground->GetText();


	_vBackground.resize(_h);
	_vForeground.resize(_h);
	for (size_t i = 0; i < _h; i++) {
		_vBackground.at(i).resize(_w);
		_vForeground.at(i).resize(_w);
	}

	for (size_t i = 0; i < _h; i++)
	{
		for (size_t j = 0; j < _w; j++)
		{
			// Background
			_len = _sMapaBg.find_first_of(',');
			_string = _sMapaBg.substr(0, _len);
			_sMapaBg = _sMapaBg.substr(_len + 1);
			_vBackground.at(i).at(j) = std::stoi(_string);

			//Foreground
			_len = _sMapaFg.find_first_of(',');
			_string = _sMapaFg.substr(0, _len);
			_sMapaFg = _sMapaFg.substr(_len + 1);
			_vForeground.at(i).at(j) = std::stoi(_string);
		}
	}
	_Rect.w = std::stoi(tileset->Attribute("tilewidth"));
	_Rect.h = std::stoi(tileset->Attribute("tileheight"));
	_tspa = std::stoi(tileset->Attribute("spacing"));
}

void Level::update()
{
}

void Level::render()
{
	for (size_t tileY = 0; tileY < _h; tileY++)
	{
		for (size_t tileX = 0; tileX < _w; tileX++)
		{
			//Background
			_Rect.x = tileX * _Rect.w;
			_Rect.y = tileY * _Rect.h;
			_ID = _vBackground.at(tileY).at(tileX) - 1;

			if (_ID >= 0) {
				_cX = _ID % 15; // la fila en X
				_cY = _ID / 15; // la fila en Y

				_RectS.x = _cX * _Rect.w + _tspa * _cX;
				_RectS.y = _cY * _Rect.h + _tspa * _cY;
				_RectS.w = _Rect.w;
				_RectS.h = _Rect.h;

				sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _RectS.w, _RectS.h, _RectS.x, _RectS.y);
			}

			//Foreground
			_Rect.x = tileX * _Rect.w;
			_Rect.y = tileY * _Rect.h;
			_ID = _vForeground.at(tileY).at(tileX) - 1;

			if (_ID >= 0) {
				_cX = _ID % 15; // la fila en X
				_cY = _ID / 15; // la fila en Y

				_RectS.x = _cX * _Rect.w + _tspa * _cX;
				_RectS.y = _cY * _Rect.h + _tspa * _cY;
				_RectS.w = _Rect.w;
				_RectS.h = _Rect.h;

				sVideo->renderGraphic(_spriteID, _Rect.x, _Rect.y, _RectS.w, _RectS.h, _RectS.x, _RectS.y);
			}

		}
	}
}
