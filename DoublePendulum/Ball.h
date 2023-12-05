#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "Mesh.h"
#include "CommonValues.h"

class Ball
{
public:
	Ball();
	Ball(int sectorCount, int stackCount, float radius, glm::vec3 pos);

	glm::vec3 pos;
	float radius;

	Mesh* mesh;

	~Ball();

private:
	GLfloat* vertices;
	unsigned int* indices;
	std::vector<GLfloat> verticesList;
	std::vector<unsigned int> indicesList;

	//Mesh Parameters
	float x, y, z, xy;
	float nx, ny, nz, lengthInv;
	float s, t;

	int k1, k2;

	float sectorStep;
	float stackStep;
	float sectorAngle, stackAngle;
};

