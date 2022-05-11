#include "Bullet.h"
#include "Video.h"
#include "ResourceManager.h"
#include <iostream>

extern Video* sVideo;
extern ResourceManager* sResourceManager;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::init(bool isFromPlayer, Vector2 initialPos, Vector2 finalPos, float speed)
{
	Vector2 direction;
	direction.x = finalPos.x - initialPos.x;
	direction.y = finalPos.y - initialPos.y;
	_direction.x = direction.x / sqrt(pow(direction.x, 2) + pow(direction.y, 2)); // Preguntar rafel
	_direction.y = direction.y / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	_isFromPlayer = isFromPlayer;
	_speed = speed;
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/bullet.png");
	std::cout << _direction.x << " " << _direction.y << std::endl;
}

void Bullet::update()
{
	_Rect.x++;
}
