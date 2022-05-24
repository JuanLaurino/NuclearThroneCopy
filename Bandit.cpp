#include "Bandit.h"
#include "Highscore.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Camera.h"

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
	_state = ST_IDLE;
	_HP = 2;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/bandit.png");
	_rectFrame.w = 24;
	_rectFrame.h = 24;
	_Rect.w = _rectFrame.w * 1.8f;
	_Rect.h = _rectFrame.h * 1.8f;
	_leftSpaceInSprite = 1;
	_spreadAngle = 20;
}

void Bandit::update()
{
	_contador += global_elapsed_time;
	if (_state != ST_FALLEN && _state != ST_ONHIT) {
		move();
	}
	switch (_state)
	{
	case Bandit::ST_IDLE:
		if (_moving) {
			_state = ST_MOVING;
			_contador = 0;
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
		if (!_moving) {
			_state = ST_IDLE;
			_contador = 0;
		}
		break;
	case Bandit::ST_FALLEN:
		break;
	default:
		break;
	}
}

void Bandit::render()
{

	_contadorAnim += global_elapsed_time;
	switch (_state)
	{
	case Bandit::ST_IDLE:
		_rectFrame.x = 0;
		_rectFrame.y = 0;
		break;
	case Bandit::ST_ONHIT:
		if (_frame >= 2) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 1 + 1;
		break;
	case Bandit::ST_MOVING:
		if (_frame >= 3) {
			_frame = 0;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = 0;

		break;
	case Bandit::ST_FALLEN:
		if (_frame >= 5) {
			_frame = 5;
		}

		_rectFrame.x = _rectFrame.w * _frame + _frame;
		_rectFrame.y = _rectFrame.h * 1 + 1;
		break;
	default:
		break;
	}

	if (_contadorAnim >= 160) {
		_frame++;
		_contadorAnim = 0;
	}

	sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _rectFrame.w - 2, _rectFrame.h - 2, _rectFrame.x + 1, _rectFrame.y + 1, _Rect.w, _Rect.h, 0, 0, 0, _dir);
}

void Bandit::shoot()
{
	Bullet* bala;
	bala = new Bullet();
	_pBullet->push_back(bala);
	_pBullet->at(_pBullet->size() - 1)->init(1, glm::vec2{ (float)(_Rect.x) + _Rect.w / 2, (float)(_Rect.y) + _Rect.h / 2 }, glm::vec2{ (float)_pPlayer->getX() + sCamera->getX(), (float)_pPlayer->getY() + sCamera->getY() }, 5, _damage, _spreadAngle);
}

void Bandit::receiveDamage(int damage)
{
	shoot();
	if (_state != ST_ONHIT && _state != ST_FALLEN) {
		_HP = _HP - damage;

		if (_HP <= 0) {
			_state = ST_FALLEN;
			// Spawn rads
			sHighscore->addScore(1);
		}
		else {
			_state = ST_ONHIT;
		}
	}
}

