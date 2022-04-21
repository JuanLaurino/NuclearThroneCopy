#include "Bullet.h"
#include "Video.h"
#include "ResourceManager.h"

extern Video* sVideo;
extern ResourceManager* sResourceManager;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::init(int direction)
{
	_spriteID = sResourceManager->loadAndGetGraphicID(sVideo->getRenderer(), "Assets/bullet.png");
}

void Bullet::update()
{
	_Rect.x++;
}
