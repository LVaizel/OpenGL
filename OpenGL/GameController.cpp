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
	m_shaderPostProcess = {};
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
	glClearColor(0, 0, 0, 1);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	srand(time(0));

	glClearColor(0, 0, 0, 1);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Resolution res = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, res.m_width, res.m_height);
	m_camera = Camera(res);
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

	m_shaderPostProcess = Shader();
	m_shaderPostProcess.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");
#pragma endregion
#pragma region CreateMeshes
	Mesh meshLight = Mesh();
	meshLight.Create(&m_shaderColor, "../Assets/Models/Sphere.obj", 1);
	meshLight.SetPosition(glm::vec3(0.0f, 0.0f, 1.8f));
	meshLight.SetColor(glm::vec3(2));
	meshLight.SetScale(glm::vec3(0.007f));
	Mesh::Lights.push_back(meshLight);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetPosition(glm::vec3(0, 0, 0));
	fighter.SetScale(glm::vec3(0.0008f));
	m_meshBoxes.push_back(fighter);
#pragma endregion
	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 48);

	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPostProcess);

#pragma region Render
	double lastTime = glfwGetTime();
	double currentTime = 0;
	int fps = 0;
	string fpsS = "0";
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//m_postProcessor.Start();

		currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1;
		}

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
		//m_postProcessor.End();

		f.RenderText(fpsS, 100.0f, 100.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

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

	f.Cleanup();
	m_postProcessor.Cleanup();

	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderSkybox.Cleanup();
	m_shaderFont.Cleanup();
	m_shaderPostProcess.Cleanup();
#pragma endregion
}
