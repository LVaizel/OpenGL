#ifndef STANDARDINCLUDES_H
#define STANDARDINCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL

//Standard Headers
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//Windows Specific Defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { \
		OutputDebugStringA(_msg); \
		std::abort(); \
		glfwTerminate(); \
	}
#endif // _WIN32

//OpenGL/Helper headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "Resolution.h"	
#include "Singleton.h"

using namespace std;

#endif // STANDARDINCLUDES_H
