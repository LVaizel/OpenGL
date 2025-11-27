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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void GameController::RunGame()
{
#pragma region LoadShaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("SkyBox.vertexshader", "SkyBox.fragmentshader");
#pragma endregion
#pragma region CreateMeshes
	Mesh meshLight = Mesh();
	meshLight.Create(&m_shaderColor, "../Assets/Models/Teapot.obj", 1);
	meshLight.SetPosition(glm::vec3(0, 0.8f, 1.0f));
	meshLight.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	meshLight.SetScale(glm::vec3(0.01f));
	Mesh::Lights.push_back(meshLight);


	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj", 1000);
	box.SetPosition(glm::vec3(0, 0, 0));
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale(glm::vec3(0.08));
	m_meshBoxes.push_back(box);

#pragma endregion
	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 48);

#pragma region Render
	double lastTime = glfwGetTime();
	double currentTime = 0;
	int fps = 0;
	string fpsS = "0";
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1;
		}
		f.RenderText(fpsS, 100.0f, 100.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		f.RenderText("BoxCount: " + to_string(m_meshBoxes.size()), 100.0f, 150.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		for (auto& light : Mesh::Lights)
		{
			light.SetRotation(light.GetRotation() + glm::vec3(0.0005f, 0, 0.0f));
			light.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (auto& box : m_meshBoxes)
		{
			box.SetRotation(box.GetRotation() + glm::vec3(0.0005f, 0, 0.0f));
			box.Render(m_camera.GetProjection() * m_camera.GetView());
		}
		glfwSwapBuffers(win);
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
#pragma endregion

#pragma region Cleanup
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
	m_shaderSkybox.Cleanup();
	m_shaderFont.Cleanup();
#pragma endregion
}
