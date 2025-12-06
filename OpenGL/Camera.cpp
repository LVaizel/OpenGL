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
	m_position = glm::vec3(0, 0, 2);
	m_projection = glm::perspective(glm::radians(45.0f), (float)_screenResolution.m_width / (float)_screenResolution.m_height, 0.1f, 1000.0f);
	m_view = glm::mat4(1.0f);

	m_rotation = glm::vec3(0, 0, 0);
	m_lookAt = glm::vec3(0, 0, 0);
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
	float rad = glm::radians(m_angle);
	m_lookAt = glm::vec3(
		cos(rad),
		0.0f,
		sin(rad)
	);

	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		glm::vec3(0, 1, 0)
	);
}

Camera::~Camera()
{
}
