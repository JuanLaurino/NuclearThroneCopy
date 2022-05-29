#include "BigMaggot.h"
#include "Highscore.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include "Main.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Highscore*		sHighscore;

BigMaggot::BigMaggot()
{
}

BigMaggot::~BigMaggot()
{
}

void BigMaggot::init()
{
	_damage = 2;
	_rads = 3;
	_HP = 4;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/bigMaggot.png");

	_state = ST_IDLE;
	_rectFrame.w = 64;
	_rectFrame.h = 64;
	_Rect.w = 64; // (int)_rectFrame.w * 1.5;
	_Rect.h = 64; //(int)_rectFrame.h * 1.5;
	_viewDistance = rand() % 500 + 200;
	_dir = false;
}

void BigMaggot::update()
{
	_contador += global_elapsed_time;
	if (_state != ST_FALLEN && _state != ST_ONHIT) {
		move();
	}
	switch (_state)
	{
	case BigMaggot::ST_IDLE:
		if (_moving || getDistance(_pPlayer->getCollision()) <= _viewDistance) {
			_state = ST_MOVING;
			_contador = 0;
		}
		break;
	case BigMaggot::ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		break;
	case BigMaggot::ST_MOVING:
		if (getDistance(_pPlayer->getCollision()) <= _viewDistance) {
			if (_pPlayer->getX() + _pPlayer->getW() / 2 >= _Rect.x + _Rect.h / 2) {
				if (_pPlayer->getX() + _pPlayer->getW() / 2 <= _Rect.x + _Rect.h / 2) {
				}
				else {
					_Rect.x++;
					_dir = true;
					checkCollision(I_D);
				}
			}
			else {
				_Rect.x--;
				_dir = false;
				checkCollision(I_A);
			}


			if (_pPlayer->getY() + _pPlayer->getH() / 2 >= _Rect.y + _Rect.w / 2) {
				if (_pPlayer->getY() + _pPlayer->getH() / 2 <= _Rect.y + _Rect.w / 2) {
				}
				else {
					_Rect.y++;
					checkCollision(I_S);
				}
			}
			else {
				_Rect.y--;
				checkCollision(I_W);
			}
		}
		else {
			move();
		}

		if (_contador >= 600) {
			_state = ST_IDLE;
			_contador = 0;
		}
		break;
	case BigMaggot::ST_FALLEN:
		if (_contador <= 100 + _corpseSpeed * 5) {
			_Rect.x += (int)round(_corpseSpeed * _XVector);
			if (_XVector > 0) {
				checkCollision(I_D);
			}
			else {
				checkCollision(I_A);
			}

			_Rect.y += (int)round(_corpseSpeed * _YVector);
			if (_YVector > 0) {
				checkCollision(I_S);
			}
			else {
				checkCollision(I_W);
			}
		}
		break;
	default:
		break;
	}
}

void BigMaggot::render()
{

	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case BigMaggot::ST_IDLE:
		_rectFrame.x = 0;
		_rectFrame.y = 0;
		break;
	case BigMaggot::ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 1 + 2;
		break;
	case BigMaggot::ST_MOVING:
		if (_frame >= 6) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = 0;

		break;
	case BigMaggot::ST_FALLEN:
		if (_frame >= 6) {
			_frame = 6;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 1 + 2;
		break;
	default:
		break;
	}

	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w, _rectFrame.h, _rectFrame.x, _rectFrame.y, 0, 0, 0, !_dir);
}

void BigMaggot::receiveDamageFromBullet(int damage, float x, float y, float speed)
{
	bool canSpawn = true;
	if (_state != ST_FALLEN) {
		_HP = _HP - damage;

		if (_HP <= 0) {
			_state = ST_FALLEN;
			_frame = 0;
			_contadorAnim = 0;
			_contador = 0;
			// Spawn rads
			spawnRads(_rads);
			_XVector = x;
			_YVector = y;
			if (speed >= 500) {
				_corpseSpeed = 1;
			}
			else if (speed >= 400) {
				_corpseSpeed = 2;
			}
			else if (speed >= 300) {
				_corpseSpeed = 3;
			}
			else if (speed >= 200) {
				_corpseSpeed = 4;
			}
			else {
				_corpseSpeed = 5;
			}

			if (rand() % 10 == 0) { // 10% chance de que spawnee un objeto
				if (rand() % 2) {
					spawnObject(0);
				}
				else {
					spawnObject(1);
				}
			}

			// Spawn maggots
			size_t size = rand() % 4;
			Maggot* maggot;
			for (size_t i = 0; i <= size; i++)
			{
				maggot = new Maggot();
				maggot->init(0);
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

