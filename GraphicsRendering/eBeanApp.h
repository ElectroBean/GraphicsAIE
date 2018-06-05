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
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "RenderTarget.h"

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

	Mesh m_cubeMesh;
	glm::mat4 m_cubeTransform;

	aie::Texture m_gridTexture;
	aie::Texture m_soulspearTexture;
	aie::Texture m_soulspearSpecularTexture;

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

	glm::vec3 m_positions[2]; 
	glm::quat m_rotations[2];

	aie::ShaderProgram m_texturedShader;
	aie::OBJMesh m_lucyMesh;
	glm::mat4 m_lucyTransform;

	aie::RenderTarget m_renderTarget;

};

