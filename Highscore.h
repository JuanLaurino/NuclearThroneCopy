#pragma once
#include <fstream>

class Highscore
{
	int _score;
	int _ranking[12];
	std::fstream _handler;
	char* _memblock;

	static Highscore* pInstance;
	int _numbersID;
	
	bool _newScore;

	void renderScore(int posY, int score);
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

	bool isNewScore() { return _newScore;	};
	void setNewScore(bool newScore) { _newScore = newScore; }

	static Highscore* getInstance();

};

