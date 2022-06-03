#include "Portal.h"
#include "Video.h"
#include "SceneDirector.h"
#include "Camera.h"

extern Video* sVideo;
extern Uint32           global_elapsed_time;

extern Camera* sCamera;
extern ResourceManager* sResourceManager;
Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::init()
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/characters/CharacterFish.png");
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.w = 10; // Cambiar por size
	_Rect.h = 10;
	_rectFrame.w = _Rect.w;
	_rectFrame.h = _Rect.h;
	_contadorAnim = 0;
	_frame = 0;
}

void Portal::update()
{
	_contadorAnim += global_elapsed_time;
	if (_contadorAnim >= 160) {
		_frame++;
		if (_frame >= 3) { // En vez de 3 total de animacion
			_frame = 0;
		}
		_contadorAnim = 0;
	}
}

void Portal::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x * _frame + 1, _rectFrame.y);
}
