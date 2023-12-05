#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "CommonValues.h"

class DoublePendulum
{
public:
	DoublePendulum();
	DoublePendulum(float r1, float r2, float m1, float m2, float a1, float a2);

	void PendulumControlling(bool* keys, GLfloat deltaTime);
	void UpdateSimulation(GLfloat deltaTime);

	float r1;
	float r2;

	float a1;
	float a2;

	~DoublePendulum();

private:
	float m1;
	float m2;

	float a1_v;
	float a2_v;
};

