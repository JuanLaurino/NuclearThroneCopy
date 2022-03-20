#pragma once
#include <fstream>

class Highscore
{
	int _score;
	int _ranking[12];
	std::fstream _handler;
	char* _memblock;
public:
	Highscore();
	~Highscore();

	void readScore();
	void renderScore();

	void addScore(int score) { _score += score; };
	void resetScore() { _score = 0; };
	void saveScore();
};

