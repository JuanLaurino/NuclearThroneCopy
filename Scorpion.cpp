#include "Scorpion.h"
#include "Highscore.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include "KeyDefine.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera* sCamera;
extern Highscore* sHighscore;

Scorpion::Scorpion()
{
}

Scorpion::~Scorpion()
{
}

void Scorpion::init()
{
	_flip = false;
	_state = ST_IDLE;
	if (rand() % 10 == 0) {
		_HP = 16;
		_damage = 6;
		_rads = 10;
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/goldenScorpion.png");
	}
	else {
		_HP = 10; 
		_damage = 4; 
		_rads = 6; 
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/Scorpion.png");
	}

	_rectFrame.w = 96;
	_rectFrame.h = 96;
	_Rect.w = _rectFrame.w;
	_Rect.h = _rectFrame.h;

	_spreadAngle = 20;
	_viewDistance = rand() % 150 + 100;
}

void Scorpion::update()
{
	_contador += global_elapsed_time;
	_shootCD -= global_elapsed_time;
	switch (_state)
	{
	case Scorpion::ST_IDLE:
		if (_contador >= 200) {
			_state = ST_MOVING;
			_contador = 0;
			_frame = 0;
		}
		break;
	case Scorpion::ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}

		break;
	case Scorpion::ST_MOVING:

		if (_pPlayer->getX() + _pPlayer->getW() / 2 >= _Rect.x - _viewDistance + _Rect.h / 2) {
			if (_pPlayer->getX() + _pPlayer->getW() / 2 <= _Rect.x + _viewDistance + _Rect.h / 2) {
				if (_pPlayer->getY() + _pPlayer->getH() / 2 >= _Rect.y - _viewDistance + _Rect.w / 2) {
					if (_pPlayer->getY() + _pPlayer->getH() / 2 <= _Rect.y + _viewDistance + _Rect.w / 2) {
						if (_shootCD <= 0) {
							shoot();
							_state = ST_ATTACKING;
							_contador = 0;
							_shootCD = rand() % 3000 + 500;
							_frame = 0;
						}
						else {
							move();
						}

						break;
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
				_Rect.x++;
				checkCollision(I_D);
			}
		}
		else {
			_Rect.x--;
			checkCollision(I_A);
		}

		if (_contador >= 600) {
			_state = ST_IDLE;
			_contador = 0;
		}
		break;
	case Scorpion::ST_ATTACKING:
		if (_contador >= 400) {
			_state = ST_IDLE;
			_contador = 0;
			_frame = 0;
		}
		break;
	case Scorpion::ST_FALLEN:
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

void Scorpion::render()
{
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case Scorpion::ST_IDLE:
		if (_frame >= 6) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 1 + 2;
		break;
	case Scorpion::ST_ONHIT:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 3 + 6;
		break;
	case Scorpion::ST_MOVING:
		if (_frame >= 6) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 2 + 4;

		break;
	case Scorpion::ST_FALLEN:
		if (_frame >= 5) {
			_frame = 5;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame * 2;
		_rectFrame.y = _rectFrame.h * 3 + 6;
		break;
	case Scorpion::ST_ATTACKING:
		if (_frame >= 2) {
			_frame = 0;
		}
		_rectFrame.x = 0;
		_rectFrame.y = 0;

		break;
	default:
		break;
	}


	if (_state == ST_FALLEN) {
		if (_flip) {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, 0, 0, 0, 1);
		}
		else {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, 0, 0, 0, 0);
		}
		return;
	}

	_flip = (_Rect.x + (_rectFrame.w / 2)) >= (_pPlayer->getX() + _pPlayer->getW() / 2);
	if (_flip) { 
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 1);
	}
	else {
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 0);
	}
}

void Scorpion::shoot()
{
	Bullet* bala;
	for (size_t i = 0; i < 7; i++)
	{
		bala = new Bullet();
		_pBullet->push_back(bala);
		_pBullet->at(_pBullet->size() - 1)->init(2, glm::vec2{ (float)(_Rect.x) + _Rect.w / 2, (float)(_Rect.y) + _Rect.h / 2 }, glm::vec2{ (float)_pPlayer->getX(), (float)_pPlayer->getY() }, 2, _damage, _spreadAngle);
	}
}

void Scorpion::receiveDamageFromBullet(int damage, float x, float y, float speed)
{
	if (_state != ST_FALLEN) {
		_HP = _HP - damage;

		if (_HP <= 0) {
			_state = ST_FALLEN;
			_frame = 0;
			_contadorAnim = 0;
			_contador = 0;

			spawnRads(_rads);
			_XVector = x;
			_YVector = y;
			if (speed >= 1000) {
				_corpseSpeed = 1;
			}
			else if (speed >= 500) {
				_corpseSpeed = 2;
			}
			else if (speed >= 400) {
				_corpseSpeed = 3;
			}
			else if (speed >= 300) {
				_corpseSpeed = 4;
			}
			else if (speed >= 200) {
				_corpseSpeed = 5;
			}
			else {
				_corpseSpeed = 6;
			}
			if (rand() % 10 == 0) { // 10% chance de que spawnee un objeto
				if (rand() % 2) {
					spawnObject(0);
				}
				else {
					spawnObject(1);
				}
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