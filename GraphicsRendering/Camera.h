#pragma once
#include <glm\ext.hpp>
#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(GLFWwindow* window);
	~Camera();

	virtual void update(float deltaTime) = 0; 
	void setPerspective(float fov, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransform() const;
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
	glm::mat4 getProjectionView() const;
	

protected:
	void updateProjectionViewTransform();
	GLFWwindow* myWindow;

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

