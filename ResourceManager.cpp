#include "ResourceManager.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::ResourceManager()
{
	_FirstFreeSlot = 0;
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	//Destroy texture es necesario?

	if (_IDMap.find(file) == _IDMap.end()) { // si no lo encuentra, no existe entonces se va
		return;
	}

	_GraphicsVector[_IDMap.find(file)->second] = NULL;
	_IDMap.erase(file);
}

Sint32 ResourceManager::loadAndGetGraphicID(SDL_Renderer* Renderer, const char* file)
{
	if (_IDMap.find(file) == _IDMap.end()) { return addGraphic(Renderer, file); }; //Creates a new graphic and returns the ID

	return _IDMap.find(file)->second; //Returns the ID of the graphic
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	for (const auto& it : _IDMap) // Look at each key-value pair
	{
		if (it.second == ID) // If value is ID
		{
			return it.first; // Return the first element in the pair
		}
	}
	return "ERROR: Graphic not found";
}

void ResourceManager::getGraphicSize(Sint32 img, int* width, int* height)
{
	Uint32 format = 0;
	int access = 0;
	SDL_QueryTexture(_GraphicsVector[img], &format, &access, width, height);
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	Uint32 format = 0;
	int access = 0;
	int width = 0;
	int height = 0;
	SDL_QueryTexture(_GraphicsVector[img], &format, &access, &width, &height);
	return width;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	Uint32 format = 0;
	int access = 0;
	int width = 0;
	int height = 0;
	SDL_QueryTexture(_GraphicsVector[img], &format, &access, &width, &height);
	return height;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	return _GraphicsVector.at(ID);
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(getGraphicByID(ID), alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	return 0;
}

ResourceManager* ResourceManager::getInstance()
{
	if (pInstance == NULL)pInstance = new ResourceManager();
	return pInstance;
}

Sint32 ResourceManager::addGraphic(SDL_Renderer* Renderer, const char* file)
{
	_FirstFreeSlot = updateFirstFreeSlotGraphic();

	SDL_Texture* imagen = IMG_LoadTexture(Renderer ,file);
	if (!imagen) {
		std::cout << "ERROR, IMAGEN \"" << file << "\" NO ENCONTRADA" << std::endl;
		system("pause");
		return -1;
	}
	if (!(_FirstFreeSlot == -1)) { //Si hay espacio libre (No es -1)
		_GraphicsVector[_FirstFreeSlot] = imagen;
		_IDMap.insert(std::pair<std::string, int>(file, _FirstFreeSlot));
	}
	else { //Si no hay espacio libre
		_GraphicsVector.push_back(imagen);
		_IDMap.insert(std::pair<std::string, int>(file, _GraphicsVector.size() - 1));
	}
	//SDL_DestroyTexture(imagen);
	return _IDMap.find(file)->second;
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	for (size_t i = 0; i < _GraphicsVector.size(); i++)
	{
		if (_GraphicsVector[i] == NULL){
			return i;
		}
	}

	return -1;
}
