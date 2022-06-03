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
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/LevelSprites/portal_opening.png");
	_Rect.x = 0;
	_Rect.y = 0;
	_Rect.w = 96; // Cambiar por size
	_Rect.h = 96;
	_rectFrame.w = _Rect.w;
	_rectFrame.h = _Rect.h;
	_contadorAnim = 0;
	_contador = 0;
	_frame = 0;
	_open = true;
	_active = true;
}

void Portal::update()
{
	_contadorAnim += global_elapsed_time;
	if (_open) {
		if (_contadorAnim >= 160) {
			_frame++;
			if (_frame >= 11) { 
				_frame = 0;
			}
			_contadorAnim = 0;
		}
	}
	else {
		if (_contadorAnim >= 320) {
			_frame++;
			if (_frame >= 11) {
				_frame = 0;
			}
			_contadorAnim = 0;
		}
	}


	if (_open) {
		if (_contador >= 1760) {
			_contador = 0;
			_contadorAnim = 0;
			_frame = 0;
			_active = false;
			return;
		}
	}
	else {

		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/LevelSprites/portal_closing.png");
		if (_contador >= 3500) {
			_contador = 0;
			_contadorAnim = 0;
			_frame = 0;
			_active = false;
			return;
		}
	}
	_contador += global_elapsed_time;
}

void Portal::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.h * _frame);
}
