#include "FlyCamera.h"



FlyCamera::FlyCamera(GLFWwindow* window)
{
	this->myWindow = window;
}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float deltaTime)
{
	//world position += forward * deltaTime * speed
	//world position += right * deltaTime * speed
	glfwGetCursorPos(myWindow, &mouseX, &mouseY);

	//radians to degrees
	deltaMouseX = (640 - mouseX) * 0.0174533f;
	deltaMouseY = (360 - mouseY) * 0.0174533f;

	glfwSetCursorPos(myWindow, 640, 360);

	glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMatrix(1.0f);

	rotMatrix = glm::rotate((float)-deltaMouseX * deltaTime, glm::vec3(up[0], up[1], up[2]));
	viewTransform = rotMatrix * viewTransform;

	rotMatrix = glm::rotate((float)-deltaMouseY * deltaTime, glm::vec3(1, 0, 0));
	viewTransform = rotMatrix * viewTransform;

	//update world transform
	worldTransform = glm::inverse(viewTransform);

	if (glfwGetKey(myWindow, GLFW_KEY_W))
	{
		worldTransform[3] -= worldTransform[2] * deltaTime * speed;
	}
	if (glfwGetKey(myWindow, GLFW_KEY_S))
	{
		worldTransform[3] += worldTransform[2] * deltaTime * speed;
	}
	if (glfwGetKey(myWindow, GLFW_KEY_A))
	{
		worldTransform[3] -= worldTransform[0] * deltaTime * speed;
	}
	if (glfwGetKey(myWindow, GLFW_KEY_D))
	{
		worldTransform[3] += worldTransform[0] * deltaTime * speed;
	}


	//worldTransform[3][3] = 1.0f;
	//viewTransform = glm::inverse(worldTransform);
	
	//word transform[3][3] = 1.0f;
	worldTransform[3][3] = 1.0f;
	//view transform = glm::inverse(m_worldtransform)
	viewTransform = glm::inverse(worldTransform);
	//UpdateProjectionViewTransform();
	updateProjectionViewTransform();
}

void FlyCamera::setSpeed(float speed)
{
	this->speed = speed;
}
