#include "HUD.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Highscore.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Highscore*		sHighscore;

extern Uint32           global_elapsed_time;

HUD::HUD()
{
	_spriteID = -1;
	_idNum = -1;
	_player = nullptr;

	_playerLevel = 0;
	_playerScore = 0;
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
	_playerScore = sHighscore->getScore();	// DESCOMENTAR
	if (_playerScore == 0) {
		_playerLevel = 0;
	}
	else
	{
		_playerLevel = _playerScore / 16;
	}
}

void HUD::render()
{
	// Cápsula de rads
	Video::getInstance()->renderGraphic(_spriteID, 8, 8, 36, 56, 0, 64);

	// Rads dentro de la cápsula
	if (_playerScore != 0) {
		int offset = 44 - (_playerScore % 16 + 1) * 2;
		Video::getInstance()->renderGraphic(_spriteID, 8, 8 + offset, 34, 32, 38, 64 + offset);
	}

	// Nivel
	Video::getInstance()->renderGraphic(_idNum, 20, 28, 12, 14, 0, _playerLevel * 16 + (_playerLevel * 2)); // EL 0 SE VE MAL?

	// Base barra de vida
	Video::getInstance()->renderGraphic(_spriteID, 36 + 2 + 8, 8, 120, 28, 0, 0);

	// Vida
	Video::getInstance()->renderGraphic(_spriteID, 36 + 2 + 8, 8, 14.5f * _player->getHP(), 28, 0, 30);

	// Números vida
	Video::getInstance()->renderGraphic(_idNum, 85, 14, 12, 14, 0, 14 * _player->getHP() + _player->getHP() * 2);
	Video::getInstance()->renderGraphic(_idNum, 100, 14, 12, 14, 0, 160);
	Video::getInstance()->renderGraphic(_idNum, 115, 14, 12, 14, 0, 14 * _player->getMaxHP() + _player->getMaxHP() * 2);
}
