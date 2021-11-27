#pragma once

#include "sdl.h"
#include "ResourceManager.h"

class Video
{
	SDL_Rect _windowRect;
	static Video* pInstance;
	Video();

public:
	~Video();
	void renderGraphic(int img, int posX, int posY, int width, int height);
	void renderGraphic(int img, int posX, int posY, int width, int height, int posXTile, int posYTile);
	void renderGraphicEx(int img, int posX, int posY, int width, int height, double angulo, int pX, int pY, int flip);
	void renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, double angulo, int pX, int pY, int flip);
	void setRenderColor(int r, int g, int b, int a = 255);
	void clearScreen();
	SDL_Renderer* getRenderer();
	void updateScreen();
	void waitTime(int ms);
	void close();
	void closeSDL();
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	static Video* getInstance();
};