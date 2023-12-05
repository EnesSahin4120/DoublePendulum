#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Mesh.h"

#include "CommonValues.h"

class Pendulum
{
public:
	Pendulum();

	Pendulum(int sectorCount, float radius, float height);
	float height;

	Mesh* mesh;

	~Pendulum();

private:
	std::vector<float> GetUnitCircleVertices();

	int sectorCount;
	float radius;

	void SetVertices();
	void SetIndices();

	std::vector<float> verticesList;
	std::vector<unsigned int> indicesList;
	float* vertices;
	unsigned int* indices;
};

