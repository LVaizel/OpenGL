#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"
class Camera
{
private:
	glm::vec3 m_position;
	glm::mat4 m_projection;
	glm::mat4 m_view;

public:
	Camera();
	Camera(Resolution _screenResolution);
	virtual ~Camera();

	glm::mat4 GetProjection() const { return m_projection; }
	glm::mat4 GetView() const { return m_view; }
	glm::vec3 GetPosition() const { return m_position; }
};

#endif // CAMERA_H

