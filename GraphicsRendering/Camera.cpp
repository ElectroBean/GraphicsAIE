#include "Camera.h"



Camera::Camera()
{
	worldTransform = glm::mat4(1.0f);
}

Camera::Camera(GLFWwindow* window)
{
	myWindow = window;
	worldTransform = glm::mat4(1.0f);
}


Camera::~Camera()
{
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(/*glm::pi<float>() **/ fov, aspectRatio, near, far);
	updateProjectionViewTransform();
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
	updateProjectionViewTransform();
}

void Camera::setPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	updateProjectionViewTransform();
}

glm::mat4 Camera::getWorldTransform() const
{
	return worldTransform;
}

glm::mat4 Camera::getView() const
{

	return viewTransform;
}

glm::mat4 Camera::getProjection() const
{

	return projectionTransform;
}

glm::mat4 Camera::getProjectionView() const
{

	return projectionViewTransform;
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform/*viewTransform * projectionTransform*/;
}
