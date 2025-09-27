#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_mesh = nullptr;
	m_shader = nullptr;
	m_camera = { };
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	m_shader = new Shader();
	m_shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = new Mesh();
	m_mesh->Create(m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	int currentSetup = 0;
	bool spacePressedLastFrame = false;

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glfwSwapBuffers(win);
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
}
