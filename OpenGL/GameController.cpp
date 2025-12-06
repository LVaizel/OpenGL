#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"
#include "Fonts.h"
#include "sstream"
#include <iomanip>

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
	meshLight.SetPosition(glm::vec3(0.0f, 0.0f, 0.8f));
	meshLight.SetColor(glm::vec3(0.8));
	meshLight.SetScale(glm::vec3(0.08f));
	Mesh::Lights.push_back(meshLight);
	Mesh& lightRef = Mesh::Lights.back();

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetPosition(glm::vec3(0, 0, 0));
	fighter.SetScale(glm::vec3(0.0008f));
	m_meshBoxes.push_back(fighter);
	Mesh& fighterRef = m_meshBoxes.back();
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
	stringstream ss;

	PrimitiveDrawTest::ToolWindow^ toolWindow = gcnew PrimitiveDrawTest::ToolWindow;
	toolWindow->Show();

	int renderState = 2;
	int lastState = -1;
	//View changes on pressing spacebar
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (toolWindow->s_MoveLightEnabled) {
			renderState = 0;
		}
		else if (toolWindow->s_TransformEnabled) {
			renderState = 1;
		}
		else if (toolWindow->s_WaterSceneEnabled) {
			renderState = 2;
		}
		else if(toolWindow->s_SpaceSceneEnabled) {
			renderState = 3;
		}

		if (renderState == 0)
		{
			if (renderState != lastState)
			{
				//Init light values
				lightRef.SetPosition(glm::vec3(0, 0, 0.8f));

				//Create fighterRef mesh with advanced lighting
				fighterRef.SetPosition(glm::vec3(0, 0, 0));
				lastState = renderState;
			}

			//Reset light position
			if (toolWindow->s_ResetLight)
			{
				lightRef.SetPosition(glm::vec3(0, 0, 0.8));
				toolWindow->s_ResetLight = false;
			}

			lightRef.SetRotation(lightRef.GetRotation() + glm::vec3(0.005f, 0.0f, 0.0f));
			lightRef.SetSpecularColor(glm::vec3(toolWindow->s_SpecularR, toolWindow->s_SpecularG, toolWindow->s_SpecularB));

			//Make the light move with mouse clicks
			MoveMeshOnMouseClick(lightRef);

			lightRef.Render(m_camera.GetProjection() * m_camera.GetView());

			fighterRef.SetRotation(fighterRef.GetRotation() + glm::vec3(0.0005f, 0.0f, 0.0f));
			fighterRef.SetSpecularStrength(toolWindow->s_SpecularStrength);
			fighterRef.Render(m_camera.GetProjection() * m_camera.GetView());

			ss << std::fixed << std::setprecision(2) << glm::to_string(lightRef.GetSpecularColor());
			f.RenderText(ss.str(), 10, 150, 0.5f, glm::vec3(1, 1, 0));
			ss.str("");
			ss.clear();
		}

		if (renderState == 1) {
			if (renderState != lastState)
			{
				lightRef.SetPosition(glm::vec3(-0.5, -0.5, 0.8f));
				fighterRef.SetRotation(glm::vec3(glm::radians(45.0f), 0, 0));
				lastState = renderState;
			}

			if(toolWindow->s_ResetTransform)
			{
				fighterRef.SetPosition(glm::vec3(0, 0, 0));
				fighterRef.SetRotation(glm::vec3(glm::radians(45.0f), 0, 0));
				fighterRef.SetScale(glm::vec3(0.0008f));
				toolWindow->s_ResetTransform = false;
			}

			if(toolWindow->s_TranslateEnabled)
			{
				MoveMeshOnMouseClick(fighterRef);
			}

			if(toolWindow->s_RotateEnabled)
			{
				RotateMeshOnMouseClick(fighterRef);
			}

			if(toolWindow->s_ScaleEnabled)
			{
				ScaleMeshOnMouseClick(fighterRef);
			}
			
			lightRef.Render(m_camera.GetProjection() * m_camera.GetView());
			fighterRef.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		if (renderState == 2) {

			if (renderState != lastState)
			{
				
			}
		}

		if (renderState == 3) {
			if (renderState != lastState)
			{
			}
		}

		double mouseX, mouseY;
		glfwGetCursorPos(win, &mouseX, &mouseY);
		int winW = 0, winH = 0;
		glfwGetWindowSize(win, &winW, &winH);

		//mouse position data won't go out of window bounds
		if (mouseX < 0) mouseX = 0;
		if (mouseY < 0) mouseY = 0;
		if (mouseX > winW) mouseX = winW;
		if (mouseY > winH) mouseY = winH;

		//Print the mouse position
		ss << std::fixed << std::setprecision(2) << "Mouse Pos: " << mouseX << " " << mouseY;
		f.RenderText(ss.str(), 10, 100, 0.5f, glm::vec3(1, 1, 0));
		ss.str("");
		ss.clear();
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

//Based on the video movement the window is split into 4 quads diagonally
//Movement is based on left and right quad mouse position relative to the diagonal
//
void GameController::MoveMeshOnMouseClick(Mesh& _mesh)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	//Leftclick adjusts xy pos in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);

		float centerX = winW * 0.5f;
		float centerY = winH * 0.5f;

		float dx = mouseX - centerX;
		float dy = centerY - mouseY;

		if (fabs(dx) < 0.0001f)
			return;

		// tan of window diagonal
		float tanC = centerY / centerX;

		// tan of mouse angle
		float tanM = dy / dx;

		if (fabs(tanM) > tanC)
			return;

		// normalized interpolation between diagonals
		float mag = tanM / tanC;    
		mag = fabs(mag);            

		float dist = sqrtf(dx * dx + dy * dy);
		float maxDist = sqrtf(centerX * centerX + centerY * centerY);

		glm::vec3 camForward = glm::normalize(m_camera.GetLookAt() - m_camera.GetPosition());
		glm::vec3 camRight = glm::normalize(glm::cross(camForward, glm::vec3(0, 1, 0)));
		glm::vec3 camUp = glm::normalize(glm::cross(camRight, camForward));

		float yMag = mag;
		float xMag = 1.0f - mag;

		// flip X on left side
		if (dx < 0)
			xMag = -xMag;

		if(dy < 0)
			yMag = -yMag;

		glm::vec3 moveDirection = xMag * camRight + yMag * camUp;

		// strength by distance from center
		float strength = dist / maxDist;
		float speed = strength * 0.002f;

		_mesh.SetPosition(_mesh.GetPosition() + moveDirection * speed);
	}

	//MiddleClick adjusts z pos in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);
		float centerY = winH * 0.5f;

		// Determine quadrant
		bool right = mouseY > centerY;

		// Camera-Aligned movement axes in relation to LookAt point
		glm::vec3 camForward = glm::normalize(m_camera.GetLookAt() - m_camera.GetPosition());

		glm::vec3 moveDirection = glm::vec3(0);

		//Decide move direction based on screen quadrant
		if (right)
			moveDirection += camForward;
		else
			moveDirection -= camForward;

		moveDirection = glm::normalize(moveDirection);

		float dirX = (float)mouseY - centerY;

		float dist = fabs(dirX);
		float maxDist = centerY;

		// Strength based on distance from screen centre
		float strength = dist / maxDist;
		float speed = strength * 0.0005f;

		// Apply movement
		_mesh.SetPosition(_mesh.GetPosition() + moveDirection * speed);
	}
}

void GameController::RotateMeshOnMouseClick(Mesh& _mesh)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	//Leftclick adjusts xy axis in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);

		float centerX = winW * 0.5f;
		float centerY = winH * 0.5f;

		float dx = mouseX - centerX;
		float dy = centerY - mouseY;

		if (fabs(dx) < 0.0001f)
			return;

		// tan of window diagonal
		float tanC = centerY / centerX;

		// tan of mouse angle
		float tanM = dy / dx;

		if (fabs(tanM) > tanC)
			return;

		// normalized interpolation between diagonals
		float mag = tanM / tanC;
		mag = fabs(mag);

		float dist = sqrtf(dx * dx + dy * dy);
		float maxDist = sqrtf(centerX * centerX + centerY * centerY);

		float yMag = mag;
		float xMag = 1.0f - mag;

		// flip X on left side
		if (dx < 0)
			xMag = -xMag;

		if (dy < 0)
			yMag = -yMag;


		glm::vec3 rotDirection = xMag * glm::vec3(1, 0, 0) + yMag * glm::vec3(0, 1, 0);

		// strength by distance from center
		float strength = dist / maxDist;
		float speed = strength * 0.002f;

		_mesh.SetRotation(_mesh.GetRotation() + (rotDirection * speed));
	}

	//MiddleClick adjusts z axis in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);
		float centerY = winH * 0.5f;

		// Determine quadrant
		bool right = mouseY > centerY;

		float dirX = (float)mouseY - centerY;

		float dist = fabs(dirX);
		float maxDist = centerY;

		// Strength based on distance from screen centre
		float strength = dist / maxDist;
		float speed = strength * 0.005f;

		glm::vec3 rotDirection = glm::vec3(0, 0, dirX < 0 ? -1 : 1);

		_mesh.SetRotation(_mesh.GetRotation() + (rotDirection * speed));
	}
}

void GameController::ScaleMeshOnMouseClick(Mesh& _mesh)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	//Leftclick adjusts xy scale in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);

		float centerX = winW * 0.5f;
		float centerY = winH * 0.5f;

		float dx = mouseX - centerX;
		float dy = centerY - mouseY;

		if (fabs(dx) < 0.0001f)
			return;

		// tan of window diagonal
		float tanC = centerY / centerX;

		// tan of mouse angle
		float tanM = dy / dx;

		if (fabs(tanM) > tanC)
			return;

		// normalized interpolation between diagonals
		float mag = tanM / tanC;
		mag = fabs(mag);

		float dist = sqrtf(dx * dx + dy * dy);
		float maxDist = sqrtf(centerX * centerX + centerY * centerY);

		float yMag = mag;
		float xMag = 1.0f - mag;

		// flip X on left side
		if (dx < 0)
			xMag = -xMag;

		if (dy < 0)
			yMag = -yMag;


		glm::vec3 scaleDirection = xMag * glm::vec3(1, 0, 0) + yMag * glm::vec3(0, 1, 0);

		// strength by distance from center
		float strength = dist / maxDist;
		float speed = strength * 0.000002f;

		_mesh.SetScale(_mesh.GetScale() + (scaleDirection * speed));
	}

	//MiddleClick adjusts z axis in context to camera LookAt point
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		int winW, winH;
		glfwGetWindowSize(window, &winW, &winH);
		float centerY = winH * 0.5f;

		// Determine quadrant
		bool right = mouseY > centerY;

		float dirX = (float)mouseY - centerY;

		float dist = fabs(dirX);
		float maxDist = centerY;

		// Strength based on distance from screen centre
		float strength = dist / maxDist;
		float speed = strength * 0.000005f;

		glm::vec3 scaleDirection = glm::vec3(0, 0, dirX < 0 ? 1 : -1);

		_mesh.SetScale(_mesh.GetScale() + (scaleDirection * speed));
	}
}
