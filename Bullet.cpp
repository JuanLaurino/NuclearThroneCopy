#include "Bullet.h"
#include "Video.h"
#include "ResourceManager.h"
#include <iostream>
#include "Audio.h"
#include "AudioManager.h"
#include "Camera.h"
#include "KeyDefine.h"

extern Video*			sVideo;
extern ResourceManager* sResourceManager;
extern Camera*			sCamera;
extern Audio*			sAudio;
extern AudioManager*	sAudioManager;

extern Uint32           global_elapsed_time;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::init(int type, glm::vec2 initialPos, glm::vec2 finalPos, float speed, int damage, int spreadAngle)
{
	_direction = finalPos - initialPos;
	_direction = glm::normalize(_direction);

	float angulo = (float)((rand() % (spreadAngle * 2 + 1) ) - spreadAngle) * 3.1415f / 180;
	_direction.x = _direction.x * cos(angulo) - _direction.y * sin(angulo);
	_direction.y = _direction.x * sin(angulo) + _direction.y * cos(angulo);

	_contadorVida = 0;

	_damage = damage;
	_bulletType = (bulletType)type;
	_speed = speed;
	_Rect.x = (int)(initialPos.x + _direction.x * 30) - 10;
	_Rect.y = (int)(initialPos.y + _direction.y * 30) - 10;

	_Rect.w = 32;
	_Rect.h = 32;
	_rectFrame.x = 0;
	_rectFrame.y = 0;
	_rectFrame.h = _Rect.h;
	_rectFrame.w = _Rect.w;

	_collidedCounter = -1;
	_collided = false;

	_angle = ((float)(atan2(_direction.x, _direction.y) * 180.0f / 3.1415f) -90.0f) * -1.0f; // Vector a grados

	switch (_bulletType)
	{
	case Bullet::Bandit_Bullet:
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/banditBullet.png");
		_rectFrame.y = 32;
		Audio::getInstance()->playAudio(-1, sAudioManager->loadAndGetAudioID("Assets/sound/shootEnemy.ogg"), 0);
		break;
	case Bullet::Scorpion_Bullet:
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/enemies/ScorpionBullet.png");
		//_IDAudioShootScorpion = sAudioManager->loadAndGetAudioID("Assets/sound/musThemeA.ogg");
		//_AudioShoot = Audio::getInstance()->playAudio(-1, _IDAudioShootScorpion, 0);
		break;
	default: // Player different bullets
		_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/characters/playerBullets.png");
		//_IDAudioShootRB = sAudioManager->loadAndGetAudioID("Assets/sound/shootEnemy.ogg");
		Audio::getInstance()->playAudio(-1, sAudioManager->loadAndGetAudioID("Assets/sound/shootSG.ogg"), 0);
		break;
	}
}

void Bullet::update()
{
	if (_bulletType == 3) {
		_contadorVida += global_elapsed_time;
		if (_contadorVida >= 300) {
			setCollided();
		}
	}

	if (_collided) {
		_collidedCounter += global_elapsed_time;
		switch ((int)round(_collidedCounter / 160))
		{
		case 0:
			_rectFrame.y = 64;
			break;
		case 1:
			_rectFrame.y = 96;
			break;
		case 2:
			_rectFrame.y = 128;
			break;
		default:
			_rectFrame.y = 160;
			break;
		}
	}
	else {
		int sumaX = (int)round(_speed * _direction.x);
		int sumaY = (int)round(_speed * _direction.y);


		if (_bulletType == Bullet::Player_SGBullet) {

			_Rect.x += sumaX;
			if (sumaX > 0) {
				checkCollisionBounce(I_D);
			}
			else {
				checkCollisionBounce(I_A);
			}

			_Rect.y += sumaY;
			if (sumaY > 0) {
				checkCollisionBounce(I_S);
			}
			else {
				checkCollisionBounce(I_W);
			}
		}
		else {
			_Rect.x += sumaX;
			_Rect.y += sumaY;
		}
	}
}

void Bullet::render()
{
	switch (_bulletType)
	{
	case Bullet::Bandit_Bullet:
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y, _angle, 16, 16, 0);
		break;
	case Bullet::Scorpion_Bullet:
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w-4, _Rect.h-4, _rectFrame.x+2, _rectFrame.y+2, _Rect.w * 1.3F, _Rect.h * 1.5F, _angle, 16, 16, 0);
		break;
	default: // Player bullets
		sVideo->renderGraphicEx(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h, _rectFrame.x, _rectFrame.y, _angle, 16, 16, 0);

		if (_collidedCounter == -1) {
			_collidedCounter = -2;
			_rectFrame.y = 32;
		}
		break;
	}
}

bool Bullet::isBulletFromPlayer()
{
	if (_bulletType == bulletType::Player_Bullet) {
		return true;
	}
	return false;
}

void Bullet::checkCollisionBounce(int direction)
{
	bool x = false;
	bool y = false;

	switch (direction)
	{
	case I_D:
		while (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y)) {
			_Rect.x--;
			x = true;
			if (collidedCount()) {
				return;
			}
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y + _Rect.h)) {
			_Rect.x--;
			x = true;
			if (collidedCount()) {
				return;
			}
		}
		break;
	case I_A:
		while (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y)) {
			_Rect.x++;
			x = true;
			if (collidedCount()) {
				return;
			}
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y + _Rect.h)) {
			_Rect.x++;
			x = true;
			if (collidedCount()) {
				return;
			}
		}
		break;
	case I_W:
		while (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y)) {
			_Rect.y++;
			y = true;
			if (collidedCount()) {
				return;
			}
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y)) {
			_Rect.y++;
			y = true;
			if (collidedCount()) {
				return;
			}
		}
		break;
	case I_S:
		while (_pLevel->getIDfromLayer(0, _Rect.x, _Rect.y + _Rect.h)) {
			_Rect.y--;
			y = true;
			if (collidedCount()) {
				return;
			}
		}
		while (_pLevel->getIDfromLayer(0, _Rect.x + _Rect.w, _Rect.y + _Rect.h)) {
			_Rect.y--;
			y = true;
			if (collidedCount()) {
				return;
			}
		}
		break;
	default:
		break;
	}
	if (x) {
		_direction.x *= -1;
		_angle = ((float)(atan2(_direction.x, _direction.y) * 180.0f / 3.1415f) - 90.0f) * -1.0f;
	}
	if (y) {
		_direction.y *= -1;
		_angle = ((float)(atan2(_direction.x, _direction.y) * 180.0f / 3.1415f) - 90.0f) * -1.0f;
	}
}

bool Bullet::collidedCount()
{
	_collidedCounterError++;
	if (_collidedCounterError >= 20) {
		_bulletType = Bullet::Player_Bullet;
		return true;
	}
	return false;
}
