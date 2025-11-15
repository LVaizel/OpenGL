#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"
#include "Fonts.h"

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	srand(time(0));

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

void GameController::RunGame()
{
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	Mesh meshLight = Mesh();
	meshLight.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	meshLight.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	meshLight.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	meshLight.SetScale(glm::vec3(0.01f));
	Mesh::Lights.push_back(meshLight);

	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot.obj");
	teapot.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale(glm::vec3(0.02f));
	m_meshBoxes.push_back(teapot);

	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj");
	box.SetPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale(glm::vec3(0.5f));
	m_meshBoxes.push_back(box);

	Mesh plane = Mesh();
	plane.Create(&m_shaderDiffuse, "../Assets/Models/Plane.obj");
	//plane.SetRotation(plane.GetRotation() + glm::vec3(0.0f, 0.7f, 0.0f));
	plane.SetPosition(glm::vec3(0, 0, -1));
	plane.SetCameraPosition(m_camera.GetPosition());
	plane.SetScale(glm::vec3(0.3f));
	m_meshBoxes.push_back(plane);

	Mesh windowMesh = Mesh();
	windowMesh.Create(&m_shaderDiffuse, "../Assets/Models/Window.obj");
	windowMesh.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	windowMesh.SetCameraPosition(m_camera.GetPosition());
	windowMesh.SetScale(glm::vec3(0.1f));
	m_meshBoxes.push_back(windowMesh);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 48);
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& light : Mesh::Lights)
		{
			//light.SetRotation(light.GetRotation() + glm::vec3(0.0f, 0.0005f, 0.0f));
			light.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (auto& box : m_meshBoxes)
		{
			box.SetRotation(box.GetRotation() + glm::vec3(0.0f, 0.0005f, 0.0f));
			box.Render(m_camera.GetProjection() * m_camera.GetView());
		}
		f.RenderText("OpenGL Game Controller - Press ESC to Exit", 10, 500, 0.5f, glm::vec3(1, 0, 0));
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
