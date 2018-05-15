#pragma once
#include <chrono>
#include <iostream>
#include <glm\ext.hpp>
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Gizmos.h"
#include "Application.h"

class eBeanApp : public Application
{
public:
	eBeanApp();
	~eBeanApp();
	
	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float deltaTime);
	virtual void Render();

protected:
	glm::mat4 view;
	glm::mat4 projection;
};

