#include "DoublePendulum.h"



DoublePendulum::DoublePendulum()
{
}

DoublePendulum::DoublePendulum(float r1, float r2, float m1, float m2, float a1, float a2)
{
	this->r1 = r1;
	this->r2 = r2;
	this->m1 = m1;
	this->m2 = m2;
	this->a1 = a1;
	this->a2 = a2;

	a1_v = 0.0f;
	a2_v = 0.0f;

	a1 *= toRadians;
	a2 *= toRadians;
}

void DoublePendulum::PendulumControlling(bool * keys, GLfloat deltaTime)
{
	GLfloat velocity = 1.5f * deltaTime;

	if (keys[GLFW_KEY_RIGHT])
		a1_v += velocity;

	if (keys[GLFW_KEY_LEFT])
		a1_v -= velocity;
}

void DoublePendulum::UpdateSimulation(GLfloat deltaTime)
{
	float numerator1 = - g * (2 * m1 + m2) * glm::sin(a1)
		               - m2 * g * glm::sin(a1 - 2 * a2)
		               + (-2 * glm::sin(a1 - a2) * m2)
		               * (a2_v * a2_v * r2 + a1_v * a1_v * r1 * glm::cos(a1 - a2));
	float denominator1 = r1 * (2 * m1 + m2 - m2 * glm::cos(2 * a1 - 2 * a2));
	float a1_a = numerator1 / denominator1;

	float numerator2 = ((2 * glm::sin(a1 - a2))
		               * ((a1_v * a1_v * r1 * (m1 + m2))
			           + (g * (m1 + m2) * glm::cos(a1))
			           + (a2_v * a2_v * r2 * m2 * glm::cos(a1 - a2))));
	float denominator2 = r2 * (2 * m1 + m2 - m2 * glm::cos(2 * a1 - 2 * a2));
	float a2_a = numerator2 / denominator2;

	a1_v += a1_a * deltaTime;
	a2_v += a2_a * deltaTime;
	a1 += a1_v;
	a2 += a2_v;

	a1_v *= 0.94f;
	a2_v *= 0.94f;
}


DoublePendulum::~DoublePendulum()
{
}
