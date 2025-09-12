#ifndef STANDARDINCLUDES_H
#define STANDARDINCLUDES_H

//Standard Headers
#include <vector>

//Windows Specific Defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { \
		OutputDebugStringA(_msg); \
		std::abort(); \
		glfwTerminate(); \
	}
#endif

//OpenGL/Helper headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "Singleton.h"

using namespace std;
#endif
