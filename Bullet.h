#pragma once
#include "GFXElement.h"
class Bullet : public GFXElement
{
	enum bulletType
	{
		Player_Bullet, Bandit_Bullet, Scorpion_Bullet
	};

	notSDL_Rect _rectFrame;

	glm::vec2 _direction;
	bulletType _bulletType;

	float _speed;
	int _damage;
	bool _collided;
	int _collidedCounter;

	float _angle;
public:
	Bullet();
	~Bullet();

	void init(int type, glm::vec2 initialPos, glm::vec2 finalPos, float speed, int damage, int spreadAngle);
	void update();
	void render();

	void setCollided() { _collided = true; };

	int getDamage() { return _damage; };
	int getCollCounter() { return _collidedCounter; };

	bool isBulletFromPlayer();
};

