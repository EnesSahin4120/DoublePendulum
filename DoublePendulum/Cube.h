#pragma once

#include <glm\glm.hpp>
#include "Mesh.h"

class Cube
{
public:
	Cube();
	Cube(glm::vec3 pos);
	void RenderMesh();

	glm::vec3 pos;

	~Cube();

private:
	Mesh* mesh;

	void CreateMesh(GLfloat *vertices, unsigned int numOfVertices);
	void ClearMesh();

	GLuint VAO, VBO;
	GLsizei indexCount;
};

