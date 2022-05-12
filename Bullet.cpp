#include "Bullet.h"
#include "Video.h"
#include "ResourceManager.h"
#include <iostream>
#include "Camera.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;
extern Camera* sCamera;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::init(bool isFromPlayer, glm::vec2 initialPos, glm::vec2 finalPos, float speed, int damage)
{
	_direction = finalPos - initialPos;
	_direction = glm::normalize(_direction);

	_damage = damage;
	_isFromPlayer = isFromPlayer;
	_speed = speed;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/bullet.png");
	_Rect.x = (int)initialPos.x + _direction.x * 30;
	_Rect.y = (int)initialPos.y + _direction.y * 30;
	_Rect.w = 16;
	_Rect.h = 16;
}

void Bullet::update()
{
	//_Rect.x += _speed * _direction.x;
	//_Rect.y += _speed * _direction.y;
	_Rect.x += (int)round(_speed * _direction.x);
	_Rect.y += (int)round(_speed * _direction.y);

}

void Bullet::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h);
}
