#include "Video.h"
#include "Main.h"
#include "SDL_image.h"
#include "Camera.h"
#include "SceneDirector.h"

Video* Video::pInstance = nullptr;

extern Camera* sCamera;

Video::Video() {
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Nuclear Juan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOWEVENT_SIZE_CHANGED);
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetIntegerScale(gRenderer, SDL_TRUE);
	SDL_RenderSetLogicalSize(gRenderer, WIN_WIDTH, WIN_HEIGHT); 

	SDL_ShowCursor(false); //Para meter mi propio cursor
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //Color por defecto negro
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}

Video::~Video() {
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height) {
	if (posX < 0 - width) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - height) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
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
	if (posX < 0 - width) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - height) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
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

void Video::renderGraphic(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, int finalWidth, int finalHeight) {
	if (posX < 0 - finalWidth) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - finalHeight) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
		return;
	}
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = finalWidth;
	r.h = finalHeight;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = posXTile;
	rectAux.y = posYTile;
	SDL_RenderCopy(gRenderer, ResourceManager::getInstance()->getGraphicByID(img), &rectAux, &r);
}

void Video::renderGraphicEx(int img, int posX, int posY, int width, int height, double angulo, int pX, int pY, int flip = 0)
{
	if (posX < 0 - width) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - height) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
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

void Video::renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, double angulo, int pXRot, int pYRot, int flip = 0)
{
	if (posX < 0 - width) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - height) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
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
	p.x = pXRot;
	p.y = pYRot;
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

void Video::renderGraphicEx(int img, int posX, int posY, int width, int height, int posXTile, int posYTile, int finalWidth, int finalHeight, double angulo, int pXRot, int pYRot, int flip = 0)
{
	if (posX < 0 - finalWidth) {
		return;
	}
	else if (posX > WIN_WIDTH) {
		return;
	}
	if (posY < 0 - finalHeight) {
		return;
	}
	else if (posY > WIN_HEIGHT) {
		return;
	}
	SDL_RendererFlip rf = SDL_FLIP_NONE;
	SDL_Point p;
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = finalWidth;
	r.h = finalHeight;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = posXTile;
	rectAux.y = posYTile;
	p.x = pXRot;
	p.y = pYRot;
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

void Video::setFullScreen(bool fs)
{
	if (fs) {
		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_BORDERLESS);
	}
}

void Video::clearScreen() {
	SDL_RenderClear(gRenderer);
}

void Video::takeScreenshot()
{
	ResourceManager::getInstance()->removeGraphic("screenshot.bmp");
	SDL_GetRendererOutputSize(gRenderer, &w, &h);
	_screenshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, _screenshot->pixels, _screenshot->pitch);
	SDL_SaveBMP(_screenshot, "screenshot.bmp");
	SDL_FreeSurface(_screenshot);
}

SDL_Renderer* Video::getRenderer()
{
	return gRenderer;
}

void Video::renderScreenshot()
{
	renderGraphic(ResourceManager::getInstance()->loadAndGetGraphicID(gRenderer, "screenshot.bmp") , 0, 0, w, h);
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