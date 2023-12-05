#include "Cube.h"

Cube::Cube() {

}

Cube::Cube(glm::vec3 pos)
{
	this->pos = pos;

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,    1.0f,  0.0f,0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,    1.0f,  1.0f,0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,    1.0f,  1.0f,0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f,0.0f,  0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,0.0f,  0.0f,  -1.0f,
		0.5f, -0.5f,  0.5f,    1.0f,  0.0f,0.0f,  0.0f,  -1.0f,
		0.5f,  0.5f,  0.5f,    1.0f,  1.0f,0.0f,  0.0f,  -1.0f,
		0.5f,  0.5f,  0.5f,   1.0f,  1.0f,0.0f,  0.0f,  -1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,0.0f,  0.0f,  -1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,0.0f,  0.0f,  -1.0f,

		-0.5f,  0.5f,  0.5f,   1.0f,  0.0f,1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f,  1.0f,1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f,  1.0f,1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f,  1.0f,1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f,  0.0f,1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,    1.0f,  0.0f,-1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,    1.0f,  1.0f,-1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,    0.0f,  1.0f,-1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,   0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,    0.0f,  0.0f,-1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,   1.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f,  1.0f, 0.0f, 1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,    1.0f,  1.0f,0.0f, 1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,    1.0f,  0.0f,0.0f, 1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,    1.0f,  0.0f,0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  1.0f,0.0f, 1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,0.0f,  -1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,    1.0f,  1.0f,0.0f,  -1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,    1.0f,  0.0f,0.0f,  -1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,    1.0f,  0.0f,0.0f,  -1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,0.0f,  -1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  -1.0f,  0.0f
	};

	mesh = new Mesh();
	CreateMesh(vertices, 288);
}

void Cube::CreateMesh(GLfloat * vertices, unsigned int numOfVertices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Cube::RenderMesh()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Cube::ClearMesh()
{
}

Cube::~Cube()
{
}
