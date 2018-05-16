#include "Application.h"

// TIME, CLOCK, AND DURATION ALIASING
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
//expected use: seconds = nanoseconds * nano_to_seconds
static const double NANO_TO_SECONDS = 0.000000001;
static const ullong NANO_IN_SECONDS = 1000000000ULL;

namespace App
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}

Application::Application()
{
}


Application::~Application()
{
}

void Application::Run(const char * title, int width, int height, bool fullscreen)
{
	if (CreateNewWindow(width, height, title, fullscreen) && Initialize())
	{
		App::clock myClock;
		App::time startTime = myClock.now();
		App::time currentTime = myClock.now();
		App::time previousTime = myClock.now();

		while (playing)
		{
			//delta Time calc
			currentTime = myClock.now();
			auto difference = currentTime - previousTime;
			float deltaTime = difference.count() * NANO_TO_SECONDS;
			

			Update(deltaTime);
			Render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	Terminate();
	DestroyWindow();
}

bool Application::Initialize()
{
	return false;
}

void Application::Render()
{

}

void Application::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool Application::CreateNewWindow(int width, int height, const char * screenName, bool fullscreen)
{
	if (glfwInit() == false)
	{
		return false;
	}
	//w   h     window name         screen*  shared
	window = glfwCreateWindow(width, height, screenName, nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	// the rest of our code goes here!
	
	//fix opengl extensions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//set clear colour
	glClearColor(0.25f, 0.25f, 0.25f, 1);

	//enable depth buffer
	glEnable(GL_DEPTH_TEST);

	return true;
}

void Application::DestroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
