#include "Bandit.h"
#include "Highscore.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"
#include "KeyDefine.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Uint32           global_elapsed_time;
extern Camera*			sCamera;
extern Highscore*		sHighscore;

Bandit::Bandit()
{
}

Bandit::~Bandit()
{
}

void Bandit::init()
{
	_weapon.init(1);
	_weapon.setState(ST_EQUIPED);
	_flip = false;
	_state = ST_IDLE;
	_HP = 2;
	_damage = 2;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/bandit.png");
	_rectFrame.w = 24;
	_rectFrame.h = 24;
	_Rect.w = (int)_rectFrame.w * 1.8f;
	_Rect.h = (int)_rectFrame.h * 1.8f;
	_leftSpaceInSprite = 1;
	_spreadAngle = 30;
	_viewDistance = rand() % 100 + 100;
}

void Bandit::update()
{
	_contador += global_elapsed_time;
	_shootCD -= global_elapsed_time;
	switch (_state)
	{
	case Bandit::ST_IDLE:
		if (_contador >= 200) {
			_state = ST_MOVING;
			_contador = 0;
			_frame = 0;
		}
		break;
	case Bandit::ST_ONHIT:
		if (_contador >= 260) {
			_contador = 0;

			_state = ST_IDLE;
			_frame = 0;
		}
		
		break;
	case Bandit::ST_MOVING:

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
	case Bandit::ST_ATTACKING:
		if (_contador >= 400) {
			_state = ST_IDLE;
			_contador = 0;
			_frame = 0;
		}
		break;
	case Bandit::ST_FALLEN:
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

void Bandit::render()
{
	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case Bandit::ST_IDLE:
		if (_frame >= 4) {
			_frame = 0;
		}
		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = 0;
		break;
	case Bandit::ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 2 + 2;
		break;
	case Bandit::ST_MOVING:
		if (_frame >= 6) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 1 + 1;

		break;
	case Bandit::ST_FALLEN:
		if (_frame >= 5) {
			_frame = 5;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 2 + 2;
		break;
	case Bandit::ST_ATTACKING:
		_frame = 0;
		_rectFrame.x = 0;
		_rectFrame.y = 0;
		break;
	default:
		break;
	}


	if (_state == ST_FALLEN) {
		if (_flip) {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 1);
		}
		else {
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 0);
		}
		return;
	}

	int weaponX = _Rect.x + _Rect.w / 2 - sCamera->getX();
	int weaponY = _Rect.y + _Rect.h / 2 - sCamera->getY() + 10;
	int delta_x = weaponX - (_pPlayer->getX() + _pPlayer->getW() / 2 - sCamera->getX());
	int delta_y = weaponY - (_pPlayer->getY() + _pPlayer->getH() / 2 - sCamera->getY());
	double angulo = (atan2(delta_y, delta_x) * 180) / 3.1416;
	// Rotacion de la bala?
	_flip = (_Rect.x + (_rectFrame.w / 2)) >= (_pPlayer->getX() + _pPlayer->getW() / 2);
	if (_flip) { // 

		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (_pPlayer->getY() + _pPlayer->getH() / 2 - sCamera->getY())) {
			// Render arma equipada
			_weapon.renderInHand(weaponX, weaponY - 5, angulo, 2);

			// Render Enemigo
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 1);

		}
		else {
			// Render Enemigo
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 1);
			// Render arma equipada
			_weapon.renderInHand(weaponX, weaponY - 5, angulo, 2);
		}
	}
	else {
		// Pintado arma
		if (_Rect.y + (_Rect.h / 2) - sCamera->getY() >= (_pPlayer->getY() + _pPlayer->getH() / 2 - sCamera->getY())) {
			// Render arma equipada
			_weapon.renderInHand(weaponX, weaponY, angulo, 0);
			// Render enemigo
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 0);
		}
		else {
			// Render personaje
			sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, 0);
			// Render arma equipada
			_weapon.renderInHand(weaponX, weaponY, angulo, 0);
		}

	}
}

void Bandit::shoot()
{
	Bullet* bala;
	bala = new Bullet();
	_pBullet->push_back(bala);
	_pBullet->at(_pBullet->size() - 1)->init(1, glm::vec2{ (float)(_Rect.x) + _Rect.w / 2, (float)(_Rect.y) + _Rect.h / 2 }, glm::vec2{ (float)_pPlayer->getX(), (float)_pPlayer->getY() }, 3, _damage, _spreadAngle);
}

void Bandit::receiveDamageFromBullet(int damage, float x, float y, float speed)
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
				_corpseSpeed = 3;
			}
			else if (speed >= 400) {
				_corpseSpeed = 5;
			}
			else if (speed >= 300) {
				_corpseSpeed = 7;
			}
			else if (speed >= 200) {
				_corpseSpeed = 9;
			}
			else {
				_corpseSpeed = 13;
			}
			if (rand() % 20 == 0) { // 5% chance de que spawnee un objeto
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