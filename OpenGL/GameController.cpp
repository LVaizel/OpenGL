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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//Dark blue background
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	m_shader = new Shader();
	m_shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = new Mesh();
	m_mesh->Create(m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	glm::mat4 view1 = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 view2 = glm::lookAt(glm::vec3(-4, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 proj1 = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 proj2 = glm::perspective(glm::radians(30.0f), 6.0f / 3.0f, 0.1f, 100.0f);

	std::vector<std::pair<glm::mat4, glm::mat4>> setups = {
		{ proj1, view1 },
		{ proj1, view2 },
		{ proj2, view1 },
		{ proj2, view2 }
	};

	int currentSetup = 0;
	bool spacePressedLastFrame = false;

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 MVP = setups[currentSetup].first * setups[currentSetup].second;
		m_mesh->Render(MVP);

		glfwSwapBuffers(win);
		glfwPollEvents();

		bool spacePressed = glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS;

		if (!spacePressed && spacePressedLastFrame) {
			currentSetup = (currentSetup + 1) % setups.size();
		}

		spacePressedLastFrame = spacePressed;

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
}
