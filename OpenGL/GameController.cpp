#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_meshBoxes.clear();
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

	for (int i = 0; i < 4; i++)
	{
		Mesh meshLight = Mesh();
		meshLight.Create(&m_shaderColor);
		meshLight.SetPosition(glm::vec3(0.5f + (float)i/10.0f, 0, -0.5f));
		meshLight.SetColor(glm::vec3(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f)));
		meshLight.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
		Mesh::Lights.push_back(meshLight);
	}

	for(int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) 
		{
			Mesh meshBox = Mesh();
			meshBox.Create(&m_shaderDiffuse);
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
		for (auto& light : Mesh::Lights)
		{
			light.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (auto& box : m_meshBoxes)
		{
			box.SetRotation(box.GetRotation() + glm::vec3(0.0f, 0.005f, 0.0f));
			box.Render(m_camera.GetProjection() * m_camera.GetView());
		}
		
		glfwSwapBuffers(win);
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
	for (auto& box : m_meshBoxes)
	{
		box.Cleanup();
	}
	for (auto& light : Mesh::Lights)
	{
		light.Cleanup();
	}
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
}
