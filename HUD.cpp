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
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/UI/HUD/HUD.png");
	_idNum = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/UI/HUD/numbers.png");
	_idAmmo = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/UI/HUD/ammo.png");
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
	Video::getInstance()->renderGraphic(_idNum, 20, 28, 12, 14, 0, _playerLevel * 16); // EL 0 SE VE MAL?

	// Base barra de vida
	Video::getInstance()->renderGraphic(_spriteID, 36 + 2 + 8, 8, 120, 28, 0, 0);

	// Vida
	Video::getInstance()->renderGraphic(_spriteID, 36 + 2 + 8, 8, 14.5f * _player->getHP(), 28, 0, 30);

	// Números vida
	Video::getInstance()->renderGraphic(_idNum, 85, 14, 12, 14, 0, 14 * _player->getHP() + _player->getHP() * 2);
	Video::getInstance()->renderGraphic(_idNum, 100, 14, 12, 14, 0, 160);
	Video::getInstance()->renderGraphic(_idNum, 115, 14, 12, 14, 0, 14 * _player->getMaxHP() + _player->getMaxHP() * 2);

	// Base Bullets
	if (_player->getHP() > 0) {
		if (_player->getInventoryWeapon0()->getType() == 3) {
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 6, 0);
		}
		else {
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 7, 0);
		}
	}
	else {
		Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 7, 0);
	}
	
	// Bullets
	if (_player->getAmmo(0) > 0){
		if (_player->getAmmo(0) <= 42)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 5, 0);
		}
		else if (_player->getAmmo(0) > 200)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 0, 0);
		}
		else if (_player->getAmmo(0) > 168)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22, 0);
		}
		else if (_player->getAmmo(0) > 126)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 2, 0);
		}
		else if (_player->getAmmo(0) > 84)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 3, 0);
		}
		else if (_player->getAmmo(0) > 42)
		{
			Video::getInstance()->renderGraphic(_idAmmo, 8, 8 + 56 + 8, 20, 22, 22 * 4, 0);
		}

	}
}
