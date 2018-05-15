#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(glm::pi<float>() * fov, aspectRatio, near, far);
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

glm::mat4 Camera::getWorldTransform()
{
	return glm::mat4();
}

glm::mat4 Camera::getView()
{

	return glm::mat4();
}

glm::mat4 Camera::getProjection()
{

	return glm::mat4();
}

glm::mat4 Camera::getProjectionView()
{

	return glm::mat4();
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform = viewTransform * worldTransform;
}
