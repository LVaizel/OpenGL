#include "Camera.h"

Camera::Camera()
{
	m_position = { };
	m_projection = { };
	m_view = { };
	m_rotation = { };
	m_lookAt = { };
	m_angle = 0.0f;
}

Camera::Camera(Resolution _screenResolution)
{
	m_position = glm::vec3(2, 2, 2);
	m_projection = glm::perspective(glm::radians(45.0f), (float)_screenResolution.m_width / (float)_screenResolution.m_height, 0.1f, 1000.0f);
	m_view = glm::mat4(1.0f);

	m_rotation = glm::vec3(0, 0, 0);
	m_lookAt = glm::vec3(1, 0, 5);
	m_angle = 0.0f;

	//Or for ortho camera
	//glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		glm::vec3(0, 1, 0)  //Head is up (set to 0, 1, 0 to look upside-down)
	);
}

void Camera::Rotate()
{
	m_angle += 0.01f;
	m_lookAt.x = cos(glm::radians(m_angle)) * 100;
	m_lookAt.z = sin(glm::radians(m_angle)) * 100;

	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		glm::vec3(0, 1, 0)  //Head is up (set to 0, 1, 0 to look upside-down)
	);
}

Camera::~Camera()
{
}
