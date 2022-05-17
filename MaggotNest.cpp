#include "MaggotNest.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Maggot.h"
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;

MaggotNest::MaggotNest()
{
	_state = ST_IDLE;
	_HP = 0;
	_damage = 0;
	_spriteID = 0;
	_Rect.w = 0;
	_Rect.h = 0;
	_rectFrame.w = 0;
	_rectFrame.h = 0;
	_contador = 0;
	_contadorAnim = 0;
	_frame = 0;
}

MaggotNest::~MaggotNest()
{
}

void MaggotNest::init()
{
	_state = ST_IDLE;
	_HP = 4;
	_damage = 2;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggotNest.png");
	_Rect.w = 64;
	_Rect.h = 64;
	_rectFrame.w = 64;
	_rectFrame.h = 64;
	_contador = 0;
	_contadorAnim = 0;
	_frame = 0;
}

void MaggotNest::update()
{
	switch (_state)
	{
	case MaggotNest::ST_FALLEN:
		break;
	case MaggotNest::ST_IDLE:
		break;
	case MaggotNest::ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		else {
			_contador += global_elapsed_time;
		}
		break;
	default:
		break;
	}
}

void MaggotNest::render()
{
	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case ST_IDLE:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.y = 0;
		break;
	case ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.y = _rectFrame.h * 1 + 2;
		break;
	case ST_FALLEN:
		if (_frame >= 1) {
			_frame = 1;
		}

		_rectFrame.y = _rectFrame.h * 2 + 4;
		break;
	default:
		break;
	}

	_rectFrame.x = _rectFrame.w * _frame + (_frame * 2);

	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y);
}

void MaggotNest::receiveDamage(int damage)
{
	if (_state != ST_ONHIT && _state != ST_FALLEN) {
		_HP = _HP - damage;

		if (_HP <= 0) {
			_state = ST_FALLEN;
			// Spawn maggots
			size_t size = rand() % 5 + 4;
			Maggot* maggot;
			for (size_t i = 0; i <= size; i++)
			{
				maggot = new Maggot();
				_enemies->push_back(maggot);
				maggot->init(sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/maggot.png"));
				maggot->setWorldPointer(_pLevel);
				maggot->setXY(_Rect.x + rand() % 20 - 10, _Rect.y + rand()% 20 - 10);
			}
		}
		else {
			_state = ST_ONHIT;
		}
	}
}
