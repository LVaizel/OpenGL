#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"
class Camera
{
private:
	glm::vec3 m_position;
	glm::mat4 m_projection;
	glm::mat4 m_view;

	glm::vec3 m_rotation;
	glm::vec3 m_lookAt;
	float m_angle;

public:
	Camera();
	Camera(Resolution _screenResolution);
	virtual ~Camera();

	glm::mat4 GetProjection() const { return m_projection; }
	glm::mat4 GetView() const { return m_view; }
	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetLookAt() const { return m_lookAt; }

	void Rotate();
};

#endif // CAMERA_H

