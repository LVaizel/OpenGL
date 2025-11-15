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
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("SkyBox.vertexshader", "SkyBox.fragmentshader");

	Mesh meshLight = Mesh();
	meshLight.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	meshLight.SetPosition(glm::vec3(90.0f, 0.0f, 10.0f));
	meshLight.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	meshLight.SetScale(glm::vec3(0.01f));
	Mesh::Lights.push_back(meshLight);

	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj");
	box.SetPosition(glm::vec3(90, 0, 0));
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale(glm::vec3(5));
	m_meshBoxes.push_back(box);

	SkyBox skybox = SkyBox();
	skybox.Create(&m_shaderSkybox, "../Assets/Models/SkyBox.obj",
		{
			"../Assets/Textures/Skybox/right.jpg",
			"../Assets/Textures/Skybox/left.jpg",
			"../Assets/Textures/Skybox/top.jpg",
			"../Assets/Textures/Skybox/bottom.jpg",
			"../Assets/Textures/Skybox/front.jpg",
			"../Assets/Textures/Skybox/back.jpg"
		});
	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 48);
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
		skybox.Render(m_camera.GetProjection() * view);

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
		f.RenderText("Cam looking at" + glm::to_string(m_camera.GetLookAt()), 10, 500, 0.5f, glm::vec3(1, 0, 0));
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
	skybox.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderSkybox.Cleanup();
	m_shaderFont.Cleanup();
}
