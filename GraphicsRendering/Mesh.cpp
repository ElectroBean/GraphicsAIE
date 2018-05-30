#include "Mesh.h"


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int * indices)
{
	assert(vao == 0);
	// generate buffers 
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	// bind vertex array aka a mesh wrapper 
	glBindVertexArray(vao);
	// bind vertex buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// fill vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	// enable first element as position 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// bind indices if there are any 
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);
		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		// fill vertex buffer 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}

	else
	{
		triCount = vertexCount / 3;
	}
	// unbind buffers 
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// MORE TO GO HERE
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// quad has 2 triangles
	triCount = 2;


	// MORE TO GO HERE
	vertices[0].normal = { 0, 1, 0, 0 };
	vertices[1].normal = { 0, 1, 0, 0 };
	vertices[2].normal = { 0, 1, 0, 0 };
	vertices[3].normal = { 0, 1, 0, 0 };
	vertices[4].normal = { 0, 1, 0, 0 };
	vertices[5].normal = { 0, 1, 0, 0 };	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,
		sizeof(Vertex), (void*)16);

	vertices[0].texCoord = { 0, 1 }; // bottom left
	vertices[1].texCoord = { 1, 1 }; // bottom right
	vertices[2].texCoord = { 0, 0 }; // top left
	vertices[3].texCoord = { 0, 0 }; // top left
	vertices[4].texCoord = { 1, 1 }; // bottom right
	vertices[5].texCoord = { 1, 0 }; // top right

    // enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)32);

}

void Mesh::initialiseCylinder()
{

}

void Mesh::initialiseQuadPyramid()
{

}

void Mesh::initialiseCube(const glm::vec3 center, glm::vec3 extents, const glm::mat4* transform)
{
	glm::vec3 vVerts[8];
	glm::vec3 c = center;
	glm::vec3 tempCenter = center;
	glm::vec3 vX(extents.x, 0, 0);
	glm::vec3 vY(0, extents.y, 0);
	glm::vec3 vZ(0, 0, extents.z);

	if (transform != nullptr) {
		vX = glm::vec3((*transform * glm::vec4(vX, 0)));
		vY = glm::vec3((*transform * glm::vec4(vY, 0)));
		vZ = glm::vec3((*transform * glm::vec4(vZ, 0)));
		tempCenter = glm::vec3((*transform)[3]) + tempCenter;
	}

	// top verts
	vVerts[0] = tempCenter - vX - vZ - vY;
	vVerts[1] = tempCenter - vX + vZ - vY;
	vVerts[2] = tempCenter + vX + vZ - vY;
	vVerts[3] = tempCenter + vX - vZ - vY;

	// bottom verts
	vVerts[4] = tempCenter - vX - vZ + vY;
	vVerts[5] = tempCenter - vX + vZ + vY;
	vVerts[6] = tempCenter + vX + vZ + vY;
	vVerts[7] = tempCenter + vX - vZ + vY;

	Vertex vTex[8];
	vTex[0].position = glm::vec4(vVerts[0], 1);
	vTex[1].position = glm::vec4(vVerts[1], 1);
	vTex[2].position = glm::vec4(vVerts[2], 1);
	vTex[3].position = glm::vec4(vVerts[3], 1);
	vTex[4].position = glm::vec4(vVerts[4], 1);
	vTex[5].position = glm::vec4(vVerts[5], 1);
	vTex[6].position = glm::vec4(vVerts[6], 1);
	vTex[7].position = glm::vec4(vVerts[7], 1);

	unsigned int indices[36] = {
		0, 1, 2, 2, 3, 0,
		0, 1, 5, 5, 4, 0, 
		2, 3, 7, 7, 6, 2, 
		3, 0, 4, 4, 7, 3, 
		7, 4, 5, 5, 6, 7, 
		6, 5, 1, 1, 2, 6, 
	};

	initialise(8, vTex, 36, indices);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	// using indices or just vertices?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);

}
