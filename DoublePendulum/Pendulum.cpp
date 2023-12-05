#include "Pendulum.h"

Pendulum::Pendulum()
{
}

std::vector<float> Pendulum::GetUnitCircleVertices()
{
	float sectorStep = 2 * pi / sectorCount;
	float sectorAngle;

	std::vector<float> unitCircleVertices;
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle));
		unitCircleVertices.push_back(0);
		unitCircleVertices.push_back(sin(sectorAngle));
	}
	return unitCircleVertices;
}

Pendulum::Pendulum(int sectorCount, float radius, float height)
{
	this->sectorCount = sectorCount;
	this->radius = radius;
	this->height = height;

	SetVertices();
	SetIndices();

	vertices = &verticesList[0];
	indices = &indicesList[0];

	mesh = new Mesh();
	mesh->CreateMesh(vertices, indices, verticesList.size(), indicesList.size());
}

void Pendulum::SetVertices()
{
	std::vector<float> unitVertices = GetUnitCircleVertices();

	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;
		float t = 1.0f - i;

		for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{

			float ux = unitVertices[k];
			float uy = unitVertices[k + 2];
			float uz = unitVertices[k + 1];

			verticesList.push_back(ux * radius);
			verticesList.push_back(h);
			verticesList.push_back(uy * radius);

			verticesList.push_back((float)j / sectorCount);
			verticesList.push_back(t);

			verticesList.push_back(ux);
			verticesList.push_back(uy);
			verticesList.push_back(uz);
		}
	}

}

void Pendulum::SetIndices()
{

	int k1 = 0;
	int k2 = sectorCount + 1;

	for (int i = 0; i < sectorCount; ++i, ++k1, ++k2)
	{
		indicesList.push_back(k1);
		indicesList.push_back(k2);
		indicesList.push_back(k1 + 1);

		indicesList.push_back(k2);
		indicesList.push_back(k2 + 1);
		indicesList.push_back(k1 + 1);
	}
}

Pendulum::~Pendulum()
{
}
