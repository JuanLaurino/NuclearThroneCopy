#include "Highscore.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "ResourceManager.h"
#include "Video.h"

Highscore* Highscore::pInstance = NULL;

extern Video* sVideo;
extern ResourceManager* sResourceManager;



Highscore* Highscore::getInstance() {
	if (!pInstance) {
		pInstance = new Highscore();
	}
	return pInstance;
}

void Highscore::renderScore(int posY, int score)
{
	int offset = 0;
	int numero = 0;
	int nScore = score;

	if (nScore == 0) {
		offset = 16 * 2;
		numero = 0;
		sVideo->renderGraphic(_numbersID, 200 + offset, posY, 14, 14, 0, 14 * numero + numero * 2);
	}

	numero = nScore % 10;
	offset = 16 * 2;

	sVideo->renderGraphic(_numbersID, 200 + offset, posY, 14, 14, 0, 14 * numero + numero * 2);

	numero = nScore % 100;
	if (numero != 0) {
		numero = numero / 10;
	}
	offset = 16 * 1;

	sVideo->renderGraphic(_numbersID, 200 + offset, posY, 14, 14, 0, 14 * numero + numero * 2);

	numero = nScore % 1000;
	if (numero != 0) {
		numero = numero / 100;
	}
	offset = 16 * 0;

	sVideo->renderGraphic(_numbersID, 200 + offset, posY, 14, 14, 0, 14 * numero + numero * 2);
}

Highscore::Highscore()
{
	for (int i = 0; i <= 11; i++) {
		_ranking[i] = 0;
	}
	_newScore = true;
	_score = 0;
}

Highscore::~Highscore()
{
}

void Highscore::init()
{
	_score = 0;
	for (int i = 0; i <= 11; i++) {
		_ranking[i] = 0;
	}

	_numbersID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/UI/HUD/numbers.png");
}

void Highscore::readScore()
{
	_ranking[10] = _score;
	_handler.open("highscore.bin", std::ios::in | std::ios::binary);  // Abro el fichero

	if (!_handler.is_open()) { // Si no existe el fichero creo uno
		std::cout << "No hay fichero de puntuaciones maximas, se creara uno." << std::endl;
		_handler.open("highscore.bin", std::ios::out | std::ios::binary);
		int numInt = 0;
		for (size_t i = 0; i < 10; i++)
		{
			_handler.write((char*)&numInt, 4);
		}
	}
	else {
		_handler.seekg(0, _handler.end);
		std::streampos size = _handler.tellg();
		_handler.seekg(0, _handler.beg);
		_memblock = new char[size];
		_handler.read(_memblock, size);
		_handler.close();

		for (size_t i = 0; i < 10; i++)
		{
			_ranking[i] = (int)_memblock[i * 4];
		}

		for (int i = 0; i <= 10; i++) {// Ordeno los primeros 10 numeros
			for (int j = 0; j <= 10; j++) {
				_ranking[11] = _ranking[j];
				if (_ranking[j] <= _ranking[j + 1]) {
					_ranking[j] = _ranking[j + 1];
					_ranking[j + 1] = _ranking[11];
				}
			}
		}
	}
}

void Highscore::saveScore()
{
	_handler.open("highscore.bin", std::ios::out | std::ios::binary); // abro el de escribir

	for (int i = 0; i < 10; i++) {
		if (_ranking[i] == 0) break;
		int numInt = _ranking[i];
		//char charComa = ',';
		_handler.write((char*)&numInt, 4);
		//_handler.write(&charComa, 1);
	}
	_handler.close();
}

void Highscore::renderScore()
{
	std::cout << "Current Score: " << _score << std::endl;
	std::cout << "TOP: " << std::endl;
	
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << i + 1 << " - " << _ranking[i] << "\n";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < 10; i++)
	{
		renderScore(88 + i * 14 + i * 2, _ranking[i]);
	}
}
