#pragma once
#include <glm\ext.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float deltaTime) = 0; 
	void setPerspective(float fov, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	

private:
	void updateProjectionViewTransform();

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

