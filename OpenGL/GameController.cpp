#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_meshBox = {};
	m_meshLight = {};
	m_shaderColor = {};
	m_shaderDiffuse = {};
	m_camera = { };
}

GameController::~GameController()
{
	
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Creates Window
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");//Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_camera = Camera(WindowController::GetInstance().GetResolution());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void GameController::RunGame()
{
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");


	m_meshLight = Mesh();
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition(glm::vec3(1.0f, -0.5f, 0));
	m_meshLight.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	m_meshBox = Mesh();
	m_meshBox.Create(&m_shaderDiffuse);
	m_meshBox.SetLightColor(glm::vec3(0.5f, 0.9f, 0.5f));
	m_meshBox.SetLightPosition(m_meshLight.GetPosition());
	m_meshBox.SetCameraPosition(m_camera.GetPosition());

	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//m_meshBox.SetRotation(m_meshBox.GetRotation() + glm::vec3(0, 0.001f, 0));
		m_meshBox.Render(m_camera.GetProjection() * m_camera.GetView());
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win);
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
	m_meshBox.Cleanup();
	m_meshLight.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
}
