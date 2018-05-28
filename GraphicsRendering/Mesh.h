#pragma once
#include <glm\ext.hpp>
#include "gl_core_4_5.h"

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {};
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialiseQuad();
	virtual void draw();

protected:

	unsigned int triCount, vao, vbo, ibo;

};

