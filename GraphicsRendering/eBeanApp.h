#pragma once
#include <chrono>
#include <iostream>
#include <glm\ext.hpp>
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include "FlyCamera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "OBJMesh.h"
#include <time.h>

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

	FlyCamera* myCamera;

	aie::ShaderProgram m_shader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	Mesh m_cubeMesh;
	glm::mat4 m_cubeTransform;

	aie::Texture m_gridTexture;

	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	aie::ShaderProgram m_normalMapShader;
	aie::OBJMesh m_spearMesh;
	glm::mat4 m_spearTransform;

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;

	aie::ShaderProgram m_phongShader;
	Light m_light;
	glm::vec3  m_ambientLight;
};

