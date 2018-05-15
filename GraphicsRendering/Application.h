#pragma once
#include <chrono>
#include <iostream>
#include <glm\ext.hpp>
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Gizmos.h"

class Application
{
public:
	Application();
	~Application();

	void Run(const char* title, int width, int height, bool fullscreen);

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	void ClearScreen();
	void quit() { playing = false; };

protected:
	virtual bool CreateNewWindow(int width, int height, const char* screenName, bool fullscreen);
	virtual void DestroyWindow();
	bool playing = true;
	GLFWwindow*	window;
};

