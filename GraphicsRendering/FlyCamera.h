#pragma once
#include "Camera.h"


class FlyCamera :
	public Camera
{
public:
	FlyCamera(GLFWwindow* window);
	~FlyCamera();

	void update(float deltaTime);
	void setSpeed(float speed);

	double mouseX;
	double mouseY;
	double deltaMouseX;
	double deltaMouseY;

protected:
	float speed;
	glm::vec3 up;

};

