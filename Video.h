#pragma once

#include "sdl.h"
#include "ResourceManager.h"

class Video
{
	static Video* pInstance;
	Video();
	SDL_Surface* _screenshot;
	int h, w;
public:
	~Video();
	void renderGraphic(int img, int posX, int posY, int width, int height);
	void renderGraphic(int img, int posX, int posY, int width, int height, int posXTile, int posYTile);
	void renderGraphic(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, int finalWidth, int finalHeight);
	void renderGraphicEx(int img, int posX, int posY, int width, int height, double angulo, int pX, int pY, int flip);
	void renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, double angulo, int pX, int pY, int flip);
	void renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, int finalWidth, int finalHeight, double angulo, int pXRot, int pYRot, int flip);
	
	void setRenderColor(int r, int g, int b, int a = 255);

	void setFullScreen(bool fs);

	void takeScreenshot();
	void renderScreenshot();

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