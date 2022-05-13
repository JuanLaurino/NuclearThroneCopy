#pragma once
#include "Fish.h"
#include "Character.h"
class HUD{
	Character* _player;
	int _spriteID;
	int _idNum;

	int _playerLevel;
	int _playerScore;
public:
	HUD();
	~HUD();

	void init();
	void update();
	void render();
	void setPlayerPointer(Character* player) { _player = player; };
};

