#include "HUD.h"
#include "ResourceManager.h"
#include "Video.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;

HUD::HUD()
{
	_spriteID = -1;
	_idNum = -1;
	_player = nullptr;
}

HUD::~HUD()
{
}

void HUD::init()
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/HUD.png");
	_idNum = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/numbers.png");
}

void HUD::update()
{
}

void HUD::render()
{
	// Cápsula de rads
	Video::getInstance()->renderGraphic(_spriteID, 8, 8, 36, 56, 0, 64);
	// Rads dentro de la cápsula
	if (_player->getRadExp() != 0) { // AUN NO FUNCIONA
		Video::getInstance()->renderGraphic(_spriteID, 8, 8 + abs((_player->getRadExp() % 16 + 1) - 16), 36, 24 + abs((_player->getRadExp() % 16 + 1) - 16), 39, 64); // 12 - 32 (16) - 12
	}
																										 // Nivel
	Video::getInstance()->renderGraphic(_idNum, 20, 28, 12, 14, 0, _player->getRadLevel() * 14 + (_player->getRadLevel() * 2));
	// Barra de vida
	Video::getInstance()->renderGraphic(_spriteID, 36 + 2 + 8, 8, 120, 28, 0, 0);
}
