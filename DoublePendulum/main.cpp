#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Material.h"

#include "Skybox.h"

#include "Cube.h"
#include "Ball.h"
#include "Pendulum.h"
#include "DoublePendulum.h"

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0,
uniformDirectionalLightTransform = 0, uniformFarPlane = 0;

Cube pivotStick;
Ball ball1;
Ball ball2;
Pendulum pendulum1;
Pendulum pendulum2;
DoublePendulum doublePendulum;

std::vector<Shader> shaderList;
Shader directionalShadowShader;

Window mainWindow;
Camera camera;

Texture ballTexture;
Texture pendulumTexture;
Texture stickTexture;

Material material;
DirectionalLight mainLight;
Skybox skybox;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	pivotStick = Cube(glm::vec3(0, 0, 0));
	pendulum1 = Pendulum(40.0f, 0.05f, 2.0f);
	ball1 = Ball(40.0f, 40.0f, 0.2f, glm::vec3(0.0f, 0.0f, 0.0f));
	pendulum2 = Pendulum(40.0f, 0.05f, 2.0f);
	ball2 = Ball(40.0f, 40.0f, 0.2f, glm::vec3(0.0f, 0.0f, 0.0f));
	doublePendulum = DoublePendulum(pendulum1.height, pendulum2.height, 1.0f, 1.0f, 0.0f, 0.0f);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
}

void RenderScene()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, pivotStick.pos);
	model = glm::scale(model, glm::vec3(3.0f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	stickTexture.UseTexture();
	material.UseMaterial(uniformSpecularIntensity, uniformShininess);
	pivotStick.RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, pivotStick.pos);
	model = glm::rotate(model, doublePendulum.a1, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, -doublePendulum.r1 * 0.5f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pendulumTexture.UseTexture();
	pendulum1.mesh->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, pivotStick.pos);
	model = glm::rotate(model, doublePendulum.a1, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, -doublePendulum.r1, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ballTexture.UseTexture();
	material.UseMaterial(uniformSpecularIntensity, uniformShininess);
	ball1.mesh->RenderMesh();
	ball1.pos = glm::vec3(model[3]);

	model = glm::mat4(1.0f);
	model = glm::translate(model, ball1.pos);
	model = glm::rotate(model, doublePendulum.a2, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, -doublePendulum.r2 * 0.5f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pendulumTexture.UseTexture();
	pendulum2.mesh->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, ball1.pos);
	model = glm::rotate(model, doublePendulum.a2, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, -doublePendulum.r2, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ballTexture.UseTexture();
	material.UseMaterial(uniformSpecularIntensity, uniformShininess);
	ball2.mesh->RenderMesh();
}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

	directionalShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glViewport(0, 0, 1366, 768);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE2);
	shaderList[0].SetTexture(1);
	shaderList[0].SetDirectionalShadowMap(2);

	shaderList[0].Validate();

	RenderScene();
}

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	ballTexture = Texture("Textures/ballTexture.jpg");
	ballTexture.LoadTexture();
	pendulumTexture = Texture("Textures/pendulumTexture.jpg");
	pendulumTexture.LoadTexture();
	stickTexture = Texture("Textures/stickTexture.jpg");
	stickTexture.LoadTexture();

	material = Material(0.3f, 4);

	mainLight = DirectionalLight(2048, 2048,
		1.0f, 1.0f, 1.0f,
		0.75f, 0.25f,
		0.0f, 0.0f, -1.0f);

	std::vector<std::string> skyboxFaces;

	skyboxFaces.push_back("Textures/Skybox/Left_Tex.png");
	skyboxFaces.push_back("Textures/Skybox/Right_Tex.png");
	skyboxFaces.push_back("Textures/Skybox/Up_Tex.png");
	skyboxFaces.push_back("Textures/Skybox/Down_Tex.png");
	skyboxFaces.push_back("Textures/Skybox/Front_Tex.png");
	skyboxFaces.push_back("Textures/Skybox/Back_Tex.png");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		doublePendulum.PendulumControlling(mainWindow.getsKeys(), deltaTime);
		doublePendulum.UpdateSimulation(deltaTime);

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		DirectionalShadowMapPass(&mainLight);
		RenderPass(camera.calculateViewMatrix(), projection);

		mainWindow.swapBuffers();
	}
	return 0;
}