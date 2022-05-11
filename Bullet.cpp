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

	std::cout << initialPos.x << " INITIAL " << initialPos.y << std::endl;
	std::cout << finalPos.x << " FINAL " << finalPos.y << std::endl;
	//double modulo = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	//_direction = direction / modulo;

	_direction = glm::normalize(_direction);

	_damage = damage;
	_isFromPlayer = isFromPlayer;
	_speed = speed;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/bullet.png");
	_Rect.x = initialPos.x;
	_Rect.y = initialPos.y;
	_Rect.w = 16;
	_Rect.h = 16;
	std::cout << _direction.x << " " << _direction.y << std::endl;
}

void Bullet::update()
{
	//_Rect.x += _speed * _direction.x;
	//_Rect.y += _speed * _direction.y;
	_Rect.x += round(_speed * _direction.x);
	_Rect.y += round(_speed * _direction.y);

}

void Bullet::render()
{
	sVideo->renderGraphic(_spriteID, _Rect.x - sCamera->getX(), _Rect.y - sCamera->getY(), _Rect.w, _Rect.h);
}
