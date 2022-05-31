#include "Canister.h"
#include "ResourceManager.h"
#include "Video.h"
#include "KeyDefine.h"
#include "Camera.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Camera*			sCamera;

extern Uint32           global_elapsed_time;

Canister::Canister()
{
}

Canister::~Canister()
{
}

void Canister::init()
{
	_type = rand() % 2; // Rand de 10¿

	if (_type == 0) {
		_damage = 0;
		_rads = rand() % 7 + 10;
		_HP = 2;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/canister.png");
		_rectFrame.w = 20;
		_rectFrame.h = 32;
		_Rect.w = _rectFrame.w;
		_Rect.h = _rectFrame.h;
		_state = ST_IDLE;
	}
	else {
		_damage = 2;
		_rads = 0;
		_HP = 4;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/canister2.png");
		_rectFrame.w = 36;
		_rectFrame.h = 44;
		_Rect.w = _rectFrame.w;
		_Rect.h = _rectFrame.h;
		_state = ST_ANIM;
	}

	_rectFrame.y = 0;
	_rectFrame.x = 0;

	_wait = rand() % 4000 + 2001;
}

void Canister::update()
{

	_contador += global_elapsed_time;

	switch (_state)
	{
	case Canister::ST_FALLEN:
		break;
	case Canister::ST_IDLE:
		if (_contador >= _wait)
		{
			_state = ST_ANIM;
			_contador = 0;
			_wait = rand() % 4000 + 2001;
			_frame = 1;
		}
		break;
	case Canister::ST_ONHIT:
		break;
	case Canister::ST_ANIM:
		if (_type == 0) {
			if (_contador >= 160 * 5) {
				_state = ST_IDLE;
				_frame = 0;
			}
		}
		break;
	default:
		break;
	}
}

void Canister::render()
{
	_contadorAnim += global_elapsed_time;
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	if (_type == 0) {
		switch (_state)
		{
		case Canister::ST_IDLE:
			_frame = 0;
			break;
		case ST_ANIM:
			if (_frame >= 7) {
				_frame = 0;
				_state = ST_IDLE;
			}
			break;
		case ST_FALLEN:
			if (_frame > 9) {
				_frame = 9;
			}
			break;
		default:
			break;
		}
	}
	else {
		switch (_state)
		{
		case Canister::ST_IDLE:
			break;
		case ST_ANIM:
			if (_frame >= 7) {
				_frame = 0;
			}
			_rectFrame.y = 0;
			break;
		case ST_FALLEN:
			if (_frame > 6) {
				_frame = 6;
			}
			_rectFrame.y = 47;
			break;
		case ST_ONHIT:
			if (_frame > 3) {
				_frame = 0;
				_state = ST_ANIM;
			}
			_rectFrame.y = 47;
			break;
		default:
			break;
		}
	}

	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _frame * _rectFrame.w + _frame * 2, _rectFrame.y);
}

void Canister::receiveDamageFromBullet(int damage, float x, float y, float speed)
{
	bool canSpawn = true;
	if (_state != ST_FALLEN) {
		if (_type == 0) {
			_state = ST_FALLEN;
			_frame = 7;
			_contadorAnim = 0;
			_contador = 0;

			spawnRads(_rads);
		}
		else {
			_HP = _HP - damage;

			if (_HP <= 0) {
				_state = ST_FALLEN;
				_frame = 4;
				_contadorAnim = 0;
				_contador = 0;
				
				size_t size = rand() % 3 + 6;
				Maggot* maggot;
				for (size_t i = 0; i <= size; i++)
				{
					maggot = new Maggot();
					maggot->init(1);
					maggot->setWorldPointer(_pLevel);
					maggot->setObjectPointer(_objects);
					do
					{
						canSpawn = true;
						maggot->setXY((_Rect.x + _Rect.w / 2 - 19) + rand() % 40, (_Rect.y + _Rect.h / 2 - 19) + rand() % 40);

						// Esquinas de la imagen
						if (_pLevel->getIDfromLayer(0, maggot->getX(), maggot->getY())) {
							canSpawn = false;
							continue;
						}
						if (_pLevel->getIDfromLayer(0, maggot->getX() + maggot->getW(), maggot->getY())) {
							canSpawn = false;
							continue;
						}
						if (_pLevel->getIDfromLayer(0, maggot->getX(), maggot->getY() + maggot->getH())) {
							canSpawn = false;
							continue;
						}
						if (_pLevel->getIDfromLayer(0, maggot->getX() + maggot->getW(), maggot->getY() + maggot->getH())) {
							canSpawn = false;
							continue;
						}

						// Centro de la imagen
						if (_pLevel->getIDfromLayer(0, maggot->getX() + maggot->getW() / 2, maggot->getY() + maggot->getH() / 2)) {
							canSpawn = false;
							continue;
						}

					} while (!canSpawn);
					_enemies->push_back(maggot);
				}

			}
			else {
				_state = ST_ONHIT;
				_frame = 0;
				_contadorAnim = 0;
				_contador = 0;
			}
		}
	}
}
