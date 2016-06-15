#pragma once
#include <glm.hpp>
#include <gtx\transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera();

	~Camera();

	mat4 getWorldToViewMtx() const;
	void mouseUpdate(const vec2 mousePos);
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	vec3& getPos();

private :
	vec3 m_pos;
	vec3 m_viewVector;
	const vec3 m_upVector;
	vec2 m_mousePos;
	vec3 m_originPos;
	const float MOVEMENT_SPEED = 0.1f;
};

