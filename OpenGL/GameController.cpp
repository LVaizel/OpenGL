#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_meshBoxes.clear();
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
	
	m_camera = Camera(WindowController::GetInstance().GetResolution());
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	srand(time(0));

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

void GameController::RunGame()
{
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");


	m_meshLight = Mesh();
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition(glm::vec3(0.5f, 0, -0.5f));
	m_meshLight.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	for(int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) 
		{
			Mesh meshBox = Mesh();
			meshBox.Create(&m_shaderDiffuse);
			meshBox.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
			meshBox.SetLightPosition(m_meshLight.GetPosition());
			meshBox.SetCameraPosition(m_camera.GetPosition());
			meshBox.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
			meshBox.SetPosition({ 0.0, -0.5f + (float)j / 10.0f, -0.2f + (float)i / 10.0f });
			m_meshBoxes.push_back(meshBox);
		}
	}

	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& box : m_meshBoxes)
		{
			box.SetRotation(box.GetRotation() + glm::vec3(0.01f, 0.001f, 0.0f));
			box.Render(m_camera.GetProjection() * m_camera.GetView());
		}
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win);
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
	for (auto& box : m_meshBoxes)
	{
		box.Cleanup();
	}
	m_meshLight.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
}
