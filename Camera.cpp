#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init(int sprite)
{
}

void Camera::update()
{
}

void Camera::render()
{
}

Camera* Camera::getInstance()
{
	if (pInstance == nullptr) pInstance = new Camera();

	return pInstance;
}
