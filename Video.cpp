#include "Video.h"
#include "Main.h"
#include "SDL_image.h"
#include "Camera.h"
#include "SceneDirector.h"

Video* Video::pInstance = nullptr;

extern Camera* sCamera;

Video::Video() {
	_windowRect.x = 0;
	_windowRect.y = 0;
	_windowRect.w = WIN_WIDTH;
	_windowRect.h = WIN_HEIGHT;

	gWindow = NULL;
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOWEVENT_SIZE_CHANGED);
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// SDL_HINT_RENDER_VSYNC | SDL_HINT_RENDER_SCALE_QUALITY
	SDL_ShowCursor(false); //Para meter mi propio cursor
	SDL_RenderSetViewport(gRenderer, &_windowRect); // Para hacer resize de la screen y que se estire
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //Color por defecto negro
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}

Video::~Video() {
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height) {
	int Xpantalla = posX - sCamera->getX();
	int Ypantalla = posY - sCamera->getY();

	if (Xpantalla < 0 - width) {
		return;
	}
	else if (Xpantalla > WIN_WIDTH) {
		return;
	}
	if (Ypantalla < 0 - height) {
		return;
	}
	else if (Ypantalla > WIN_HEIGHT) {
		return;
	}

	SDL_Rect r;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	SDL_RenderCopy(gRenderer, ResourceManager::getInstance()->getGraphicByID(img), NULL, &r); // NULL porque pinta todo el sprite
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height, int posXTile, int posYTile) {
	int Xpantalla = posX - sCamera->getX();
	int Ypantalla = posY - sCamera->getY();

	if (Xpantalla < 0 - width) {
		return;
	}
	else if (Xpantalla > WIN_WIDTH) {
		return;
	}
	if (Ypantalla < 0 - height) {
		return;
	}
	else if (Ypantalla > WIN_HEIGHT) {
		return;
	}
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY; 
	r.w = width;
	r.h = height;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = posXTile;
	rectAux.y = posYTile;
	SDL_RenderCopy(gRenderer, ResourceManager::getInstance()->getGraphicByID(img), &rectAux, &r);
}

void Video::renderGraphicEx(int img, int posX, int posY, int width, int height, double angulo, int pX, int pY, int flip)
{
	int Xpantalla = posX - sCamera->getX();
	int Ypantalla = posY - sCamera->getY();

	if (Xpantalla < 0 - width) {
		return;
	}
	else if (Xpantalla > WIN_WIDTH) {
		return;
	}
	if (Ypantalla < 0 - height) {
		return;
	}
	else if (Ypantalla > WIN_HEIGHT) {
		return;
	}

	SDL_RendererFlip rf = SDL_FLIP_NONE;
	SDL_Point p;
	SDL_Rect r;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	p.x = pX;
	p.y = pY;
	switch (flip)
	{
	case 1:
		rf = SDL_FLIP_HORIZONTAL;
		break;
	case 2:
		rf = SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}
	SDL_RenderCopyEx(gRenderer, ResourceManager::getInstance()->getGraphicByID(img), NULL, &r, angulo, &p, rf);
}

void Video::renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, double angulo, int pX, int pY, int flip = 0)
{
	int Xpantalla = posX - sCamera->getX();
	int Ypantalla = posY - sCamera->getY();

	if (Xpantalla < 0 - width) {
		return;
	}
	else if (Xpantalla > WIN_WIDTH) {
		return;
	}
	if (Ypantalla < 0 - height) {
		return;
	}
	else if (Ypantalla > WIN_HEIGHT) {
		return;

	}
	SDL_RendererFlip rf = SDL_FLIP_NONE;
	SDL_Point p;
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = posXTile;
	rectAux.y = posYTile;
	p.x = pX;
	p.y = pY;
	switch (flip)
	{
	case 0:
		rf = SDL_FLIP_NONE;
		break;
	case 1:
		rf = SDL_FLIP_HORIZONTAL;
		break;
	case 2:
		rf = SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}
	SDL_RenderCopyEx(gRenderer, ResourceManager::getInstance()->getGraphicByID(img), &rectAux, &r, angulo, &p, rf);
}

void Video::setRenderColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
}

void Video::clearScreen() {
	SDL_RenderClear(gRenderer);
}

SDL_Renderer* Video::getRenderer()
{
	return gRenderer;
}

void Video::updateScreen() {
	SDL_RenderPresent(gRenderer);
}

void Video::waitTime(int ms) {
	SDL_Delay(ms);
}

void Video::close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
}

void Video::closeSDL()
{
	SDL_Quit();
}

Video* Video::getInstance()
{
	if (pInstance == nullptr) pInstance = new Video();

	return pInstance;
}