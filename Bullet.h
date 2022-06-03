#pragma once
#include "GFXElement.h"
#include "Level.h"

class Bullet : public GFXElement
{
	enum bulletType
	{
		Player_Bullet, Bandit_Bullet, Scorpion_Bullet, Player_SGBullet
	};

	notSDL_Rect _rectFrame;

	glm::vec2 _direction;
	bulletType _bulletType;
	Level* _pLevel;

	float _speed;
	int _damage;
	bool _collided;
	int _collidedCounter;
	int _contadorVida;
	int _collidedCounterError;

	float _angle;
public:
	Bullet();
	~Bullet();

	void init(int type, glm::vec2 initialPos, glm::vec2 finalPos, float speed, int damage, int spreadAngle);
	void update();
	void render();

	void setCollided() { _collided = true; };
	void setWorldPointer(Level* nivel) { _pLevel = nivel; };

	int getDamage() { return _damage; };
	int getCollCounter() { return _collidedCounter; };
	float getSpeedX() { return _direction.x; };
	float getSpeedY() { return _direction.y; };
	int getType() { return _bulletType; };

	bool isBulletFromPlayer();
	void checkCollisionBounce(int direction);
	bool collidedCount();
};

