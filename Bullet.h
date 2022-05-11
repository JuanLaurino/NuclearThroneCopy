#pragma once
#include "GFXElement.h"
class Bullet : public GFXElement
{
	Vector2 _direction;
	bool _isFromPlayer;
	float _speed;
public:
	Bullet();
	~Bullet();

	void init(bool isFromPlayer, Vector2 initialPos, Vector2 finalPos, float speed);
	void update();
};

