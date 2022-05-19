#pragma once
#include <fstream>

class Highscore
{
	int _score;
	int _ranking[12];
	std::fstream _handler;
	char* _memblock;

	static Highscore* pInstance;
public:
	Highscore();
	~Highscore();

	void init();
	void readScore();
	void renderScore();

	int getScore() { return _score; };
	void addScore(int score) { _score += score; };
	void resetScore() { _score = 0; };
	void saveScore();

	static Highscore* getInstance();

};

