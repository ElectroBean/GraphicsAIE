#include "eBeanApp.h"

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

eBeanApp::eBeanApp()
{

}


eBeanApp::~eBeanApp()
{
}

bool eBeanApp::Initialize()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);
	view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	myCamera = new FlyCamera(window);
	myCamera->setSpeed(25.0f);
	myCamera->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	myCamera->setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	myCamera->setPosition(glm::vec3(0, 10, 10));

	//shader stuff
	//m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");
	//m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");
	//if (m_shader.link() == false)
	//{
	//	printf("Shader Error: %s\n", m_shader.getLastError());
	//	return false;
	//}
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/textured.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/textured.frag");
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
	//m_quadMesh.initialiseQuad();
	//
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1,
	};

	// define 4 vertices for 2 triangles 
	Mesh::Vertex vertices2[4];
	vertices2[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices2[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices2[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices2[3].position = { 0.5f, 0, -0.5f, 1 };
	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	m_quadMesh.initialise(4, vertices2, 6, indices);


	m_cubeTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	m_cubeMesh.initialiseCube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), &m_cubeTransform);

	if (m_gridTexture.load("../textures/numbered_grid.tga") == false)
	{
		printf("failed to load texture!\n");
		return false;
	}


	return true;
}

void eBeanApp::Terminate()
{
	aie::Gizmos::destroy();
}

void eBeanApp::Update(float deltaTime)
{
	aie::Gizmos::addTransform(glm::mat4(1));

	myCamera->update(deltaTime);

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
	
	int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if (state != 0)
	{
		quit();
	}
}

void eBeanApp::Render()
{
	ClearScreen();

	//bind shader
	m_shader.bind();

	////bindtransform
	//auto pvm = myCamera->getProjectionView() * m_quadTransform;
	//m_shader.bindUniform("ProjectionViewModel", pvm);
	////draw quad
	//m_quadMesh.draw(); 


	auto pvm2 = myCamera->getProjectionView();
	m_shader.bindUniform("ProjectionViewModel", pvm2);

	m_shader.bindUniform("diffuseTexture", 0);
	m_gridTexture.bind(0);
	m_cubeMesh.draw();

	aie::Gizmos::draw(myCamera->getProjectionView());	aie::Gizmos::draw2D(1280, 720);
}

