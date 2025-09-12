#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"

GameController::GameController()
{
	m_mesh = nullptr;
	m_shader = nullptr;
}

GameController::~GameController()
{
	if (m_mesh != nullptr)
	{
		m_mesh->Cleanup();
		delete m_mesh;
		m_mesh = nullptr;
	}
	if (m_shader != nullptr)
	{
		m_shader->Cleanup();
		delete m_shader;
		m_shader = nullptr;
	}
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Creates Window
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");//Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//Dark blue background
}

void GameController::RunGame()
{
	m_shader = new Shader();
	m_shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = new Mesh();
	m_mesh->Create(m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		glClear(GL_COLOR_BUFFER_BIT);//Clear screen
		m_mesh->Render();//Draw triangle
		glfwSwapBuffers(win); //Swap the front and back buffer
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
}
