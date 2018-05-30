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
	myCamera->setSpeed(10.0f);
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


	if (m_spearMesh.load("../meshes/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear mesh error!\n");
		return false;
	}

	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");
	if (m_normalMapShader.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert");	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	if (m_dragonMesh.load("../meshes/stanford/dragon.obj", true, true) == false)
	{
		printf("dragon mesh error!\n");
		return false;
	}

	m_dragonTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	//lighting
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 }; 
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

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

	float time = GetCurrentTime(time);
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

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
	//m_shader.bind();
	//m_normalMapShader.bind();
	m_phongShader.bind();

	//bind light
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	m_phongShader.bindUniform("cameraPosition", myCamera->getWorldTransform()[3]);

	//bind tarnsform
	auto pvm3 = myCamera->getProjectionView() * m_spearTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm3);

	//auto pvm4 = myCamera->getProjectionView() * m_dragonTransform;
	//m_phongShader.bindUniform("ProjectionViewModel", pvm4);

	//bind transforms for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));
	//m_spearMesh.draw();
	m_dragonMesh.draw();

	aie::Gizmos::draw(myCamera->getProjectionView());
	aie::Gizmos::draw2D(1280, 720);
}

