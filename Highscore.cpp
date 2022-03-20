#include "Highscore.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

Highscore::Highscore()
{
	for (int i = 0; i <= 11; i++) {
		_ranking[i] = 0;
	}
}

Highscore::~Highscore()
{
}

void Highscore::readScore()
{
	_ranking[10] = _score;
	_handler.open("highscore.bin", std::ios::in | std::ios::binary);  // Abro el fichero

	if (!_handler.is_open()) { // Si no existe el fichero creo uno
		std::cout << "No hay fichero de puntuaciones maximas, se creara uno." << std::endl;
		_handler.open("highscore.bin", std::ios::out | std::ios::binary);
		int numInt = _ranking[10];
		_handler.write((char*)&numInt, 4);
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
	for (int i = 0; i <= 11; i++) {
		_ranking[i] = 3;
	}
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
	//_text[10] = "PRESIONA R PARA VOLVER AL MENU";
	//_text[11] = "PUNTUACIONES MAXIMAS ";
	//Render.DrawFrase(_text[11], 75, 30);
	//for (int i = 0; i <= 10; i++) {
	//	Render.DrawFrase(_text[i], 75, 50 + i * 10); //Muestro por pantalla
	//}

	
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << _ranking[i] << std::endl;
	}

	/*
	for (size_t i = 0; i <= 10; i++)
	{
		std::cout << i << " - " << _ranking[i] << std::endl;
	}*/
}
