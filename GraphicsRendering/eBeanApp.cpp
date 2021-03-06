#include "eBeanApp.h"

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
	myCamera->setSpeed(15.f);
	myCamera->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	myCamera->setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	myCamera->setPosition(glm::vec3(0, 10, 10));


	if (m_treeDude.load("../meshes/treedude/forest-monster.obj", true, true) == false)
	{
		printf("tree dude mesh error!\n");
		return false;
	}

	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_spearMesh.load("../meshes/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear mesh error!\n");
		return false;
	}

	m_treeDudeTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};


	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/textured.frag");
	if (m_texturedShader.link() == false)
	{
		printf("Shader Error: %s\n", m_texturedShader.getLastError());
		return false;
	}

	if (m_renderTarget.initialise(1, 1280,
		720) == false) {
		printf("Render Target Error!\n");
		return false;
	}

	//lighting
	//m_light.diffuse = { 1, 1, 0 };
	//m_light.specular = { 1, 1, 0 };
	//
	//m_secondLight.direction = { 0, 0, 1 };
	//m_secondLight.diffuse = { 1, 1, 0 };
	for (int i = 0; i < 2; i++)
	{
		directionalLights[i].diffuse = { 1, 1, 1 };
		directionalLights[i].specular = { 1, 1, 1 };
		directionalLights[i].direction = { 0, 0, 1 };
	}
	//m_secondLight.specular = { 1, 1, 0 };

	m_ambientLight = { 0, 0, 0};

	m_positions[0] = glm::vec3(10, 5, 10);
	m_positions[1] = glm::vec3(-10, 0, -10);
	m_rotations[0] = glm::quat(glm::vec3(0, -1, 0));
	m_rotations[1] = glm::quat(glm::vec3(0, 1, 0));

	return true;
}

void eBeanApp::Terminate()
{
	aie::Gizmos::destroy();
}

void eBeanApp::Update(float deltaTime)
{
	aie::Gizmos::clear();
	myCamera->update(deltaTime);

	float time = glfwGetTime();
	directionalLights[0].direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

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

	// use time to animate a value between [0, 1]
	float s = glfwGetTime() * 0.5f + 0.5f;
	// standard linear interpolation
	glm::vec3 p = (1.0f - s) * m_positions[0] + s * m_positions[1];
	// quaternion slerp
	glm::quat r = glm::slerp(m_rotations[0], m_rotations[1], s);
	// build a matrix
	glm::mat4 m = glm::translate(p) * glm::toMat4(r);
	// draw a transform and box
	aie::Gizmos::addTransform(m);
	aie::Gizmos::addAABBFilled(p, glm::vec3(.5f), glm::vec4(1, 0, 0, 1), &m);

	int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if (state != 0)
	{
		quit();
	}
}

void eBeanApp::Render()
{
	//m_renderTarget.bind();
	//wipe the screen to the background colour
	ClearScreen();
	
	m_phongShader.bind();
	
	//bind light
	m_phongShader.bindUniform("Ia", m_ambientLight);

	//replacing with multiple
	//m_phongShader.bindUniform("Id", m_light.diffuse);
	//m_phongShader.bindUniform("Is", m_light.specular);
	//m_phongShader.bindUniform("directionalLights", directionalLights);
	//m_phongShader.bindUniform("LightDirection", m_light.direction);

	//binding lighting
	for (int i = 0; i < 2; i++)
	{
		std::string directionStr = "directionalLights[" + std::to_string(i) + "].direction";
		std::string diffuseStr = "directionalLights[" + std::to_string(i) + "].diffuse";
		std::string specularStr = "directionalLights[" + std::to_string(i) + "].specular";

		const char* dir = directionStr.c_str();
		const char* diff = diffuseStr.c_str();
		const char* spec = specularStr.c_str();

		m_phongShader.bindUniform(dir, directionalLights[i].direction);
		m_phongShader.bindUniform(diff, directionalLights[i].diffuse);
		m_phongShader.bindUniform(spec, directionalLights[i].specular);
	}
	m_phongShader.bindUniform("cameraPosition", myCamera->getWorldTransform()[3]);
	
	
	//bind tarnsform
	auto pvm = myCamera->getProjectionView() * m_spearTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	//bind transforms for lighting
	m_phongShader.bindUniform("diffuseTexture", m_spearTransform);
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));

	m_spearMesh.draw();

	//unbind target to retun to backbuffer
	//m_renderTarget.unbind();

	//clear back buffer
	//ClearScreen();
	
	//m_texturedShader.bind();
	//pvm = myCamera->getProjectionView() * m_lucyTransform;
	//m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	//m_texturedShader.bindUniform("diffuseTexture", 0);
	//m_renderTarget.getTarget(0).bind(0);
	


	//draw quadmesh
	//m_bunnyMesh.draw();
	//m_lucyMesh.draw();
	
	aie::Gizmos::draw(myCamera->getProjectionView());
	aie::Gizmos::draw2D(1280, 720);

	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//bind tarnsform
	pvm = myCamera->getProjectionView() * m_treeDudeTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	//bind transforms for lighting
	m_phongShader.bindUniform("diffuseTexture", m_treeDudeTransform);
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_treeDudeTransform)));

	m_treeDude.draw();
	
	glEnable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
	glDisable(GL_ALPHA);
	//glDepthMask(GL_TRUE);


}
