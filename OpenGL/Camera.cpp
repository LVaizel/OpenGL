#include "Camera.h"

Camera::Camera()
{
	m_position = { };
	m_projection = { };
	m_view = { };
}

Camera::Camera(Resolution _screenResolution)
{
	m_position = glm::vec3(1, 1, 1);
	m_projection = glm::perspective(glm::radians(45.0f), (float)_screenResolution.m_width / (float)_screenResolution.m_height, 0.1f, 1000.0f);
	m_view = glm::mat4(1.0f);

	//Or for ortho camera
	//glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	m_view = glm::lookAt(
		m_position, //Camera is at (2, 2, 2), in World Space
		glm::vec3(0, 0, 0), //and looks at the origin
		glm::vec3(0, 1, 0)  //Head is up (set to 0, 1, 0 to look upside-down)
	);
}

Camera::~Camera()
{
}
