#pragma once
#include "GFXElement.h"
class Bullet : public GFXElement
{
	glm::vec2 _direction;
	bool _isFromPlayer;
	float _speed;
	int _damage;
public:
	Bullet();
	~Bullet();

	void init(bool isFromPlayer, glm::vec2 initialPos, glm::vec2 finalPos, float speed, int damage);
	void update();
	void render();

	int getDamage() { return _damage; };
};

