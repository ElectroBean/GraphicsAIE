#include <iostream>
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Gizmos.h"
#include <glm\ext.hpp>
#include <chrono>
#include "eBeanApp.h"

//parent
glm::mat4 parentMatrix(1);

//child
glm::mat4 localMatrix(1);
glm::mat4 globalMatrix(1);

// TIME, CLOCK, AND DURATION ALIASING
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
//expected use: seconds = nanoseconds * nano_to_seconds
static const double NANO_TO_SECONDS = 0.000000001;
static const ullong NANO_IN_SECONDS = 1000000000ULL;

namespace eBean
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}

int main()
{
	eBeanApp newApp;
	//newApp.Initialize();
	newApp.Run("asd", 1280, 720, false);

	eBean::clock myClock;
	eBean::time startTime = myClock.now();
	eBean::time currentTime = myClock.now();
	eBean::time previousTime = myClock.now();

	parentMatrix[3] = glm::vec4(0, 0, 5, 1);
	localMatrix[3] = glm::vec4(0, 0, -2, 1);

	globalMatrix = parentMatrix * localMatrix;

	glm::mat4 rot(1);
	rot = glm::rotate(rot, 0.7853975f, glm::vec3(0, 1, 0));
	parentMatrix = parentMatrix * rot;
	localMatrix[3] = glm::vec4(0, 0, -2, 1);
	globalMatrix = parentMatrix * localMatrix;


	//if (glfwInit() == false)
	//{
	//
	//	return -1;
	//}
	//
	////w   h     window name         screen*  shared
	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	//if (window == nullptr) {
	//	glfwTerminate();
	//	return -2;
	//}
	//glfwMakeContextCurrent(window);
	//// the rest of our code goes here!
	//
	////fix opengl extensions
	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}
	//
	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);
	//
	////set clear colour
	//glClearColor(0.25f, 0.25f, 0.25f, 1);
	//
	////enable depth buffer
	//glEnable(GL_DEPTH_TEST);
	//
	////create gizmos
	//aie::Gizmos::create(10000, 10000, 10000, 10000);
	//glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	//glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	//
	//while (glfwWindowShouldClose(window) == false &&
	//	glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	//check time
	//	previousTime = currentTime;
	//	currentTime = myClock.now();
	//
	//	auto difference = currentTime - previousTime;
	//
	//
	//	float deltaTime = difference.count() * NANO_TO_SECONDS;
	//	std::cout << deltaTime << std::endl;
	//
	//	//clear
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	// our game logic and update code goes here!
	//	// so does our render code!
	//
	//	aie::Gizmos::clear();
	//	aie::Gizmos::addTransform(glm::mat4(1));
	//
	//	glm::vec4 white(1);
	//	glm::vec4 black(0, 0, 0, 1);
	//
	//	for (int i = 0; i < 21; i++)
	//	{
	//		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
	//			glm::vec3(-10 + i, 0, -10),
	//			i == 10 ? white : black);
	//
	//		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
	//			glm::vec3(-10, 0, -10 + i),
	//			i == 10 ? white : black);
	//	}
	//	//draw my shit
	//	//aie::Gizmos::addAABBFilled(glm::vec3(0, 1, 0), glm::vec3(1, 1, 1), glm::vec4(1, 0, 0, 1));
	//	//aie::Gizmos::addSphere(glm::vec3(0, 3, 0), 1, 50, 50, glm::vec4(0, 1, 1, 1));
	//	//aie::Gizmos::addCapsule(glm::vec3(5, 5, 0), 5, 1, 50, 50, glm::vec4(0, 1, 1, 0));
	//
	//
	//	//rotate parent around sun
	//	glm::mat4 rot(1);
	//	rot = glm::rotate(rot, deltaTime, glm::vec3(0, 1, 0));
	//	parentMatrix = rot * parentMatrix;
	//
	//	//rotate parent itself
	//	rot = glm::rotate(rot, deltaTime, glm::vec3(0, 1, 0));
	//	parentMatrix = parentMatrix * rot;
	//
	//	//child rotation around parent
	//	rot = glm::rotate(rot, deltaTime, glm::vec3(0, 1, 0));
	//	localMatrix = rot * localMatrix;
	//
	//	//child rotation around self
	//	rot = glm::rotate(rot, deltaTime, glm::vec3(0, 1, 0));
	//	localMatrix = localMatrix * rot;
	//	
	//	globalMatrix = parentMatrix * localMatrix;
	//
	//	//parent
	//	aie::Gizmos::addSphere(parentMatrix[3], 1, 10, 10, glm::vec4(1, 1, 0, 1), &parentMatrix);
	//	//child
	//	aie::Gizmos::addSphere(globalMatrix[3], 1, 10, 10, glm::vec4(1, 0, 0, 1), &globalMatrix);
	//
	//	aie::Gizmos::draw(projection * view);
	//
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
}