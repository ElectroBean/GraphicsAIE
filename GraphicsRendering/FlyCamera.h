#pragma once
#include "Camera.h"


class FlyCamera :
	public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(float deltaTime);
	void setSpeed(float speed);

private:
	float speed;
	glm::vec3 up;
};
