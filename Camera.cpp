#include "Camera.h"



Camera::Camera() :
	m_viewVector(-0.6f, -0.1f, -0.1f),
	m_pos(0.2f, 3.6f, 4.53f),
	m_upVector(0.0f, 1.0f, 0.0f)
{
}


Camera::~Camera()
{
}

mat4 Camera::getWorldToViewMtx() const {
	return glm::lookAt(m_pos, m_pos + m_viewVector, m_upVector);
}

vec3& Camera::getPos() {
	return m_pos;
}

void Camera::mouseUpdate(const vec2 mousePos) {

	const float ROT_SPEED = 0.01f;
	vec2 deltaVector = (mousePos - m_mousePos);
	m_mousePos = mousePos;

	if (glm::length(deltaVector) > 100.0f)
		return;

	m_originPos = glm::cross(m_viewVector, m_upVector);
	mat4 mtxRotate = glm::rotate(-deltaVector.x * ROT_SPEED, m_upVector) *
		glm::rotate(-deltaVector.y * ROT_SPEED, m_originPos);

	m_viewVector = glm::mat3(mtxRotate) * m_viewVector;

}

void Camera::moveForward()
{
	m_pos += MOVEMENT_SPEED * m_viewVector;
}

void Camera::moveBackward()
{
	m_pos -= MOVEMENT_SPEED * m_viewVector;
}

void Camera::moveLeft()
{
	m_pos -= MOVEMENT_SPEED * m_originPos;
}

void Camera::moveRight()
{
	m_pos += MOVEMENT_SPEED * m_originPos;
}

void Camera::moveUp()
{
	m_pos += MOVEMENT_SPEED * m_upVector;
}

void Camera::moveDown()
{
	m_pos -= MOVEMENT_SPEED * m_upVector;
}
