#include "Mouse.h"

Mouse::Mouse()
{
	init();
}

Mouse::~Mouse()
{
	clear();
}

void Mouse::init(){
	m_pBtnEvent = new SDL_MouseButtonEvent();
	m_pWheelEvent = new SDL_MouseWheelEvent();
	m_pMotionEvent = new SDL_MouseMotionEvent();
}

void Mouse::clear() {
	m_pBtnEvent = nullptr;
	m_pWheelEvent = nullptr;
	m_pMotionEvent = nullptr;
}

void Mouse::ProcessSDLEvent(SDL_Event& e)
{
	m_pBtnEvent =& e.button;
	m_pWheelEvent =& e.wheel;
	m_pMotionEvent = &e.motion;
}

int Mouse::getPosX()
{
	return m_pMotionEvent->x;
}

int Mouse::getPosY()
{
	return m_pMotionEvent->y;
}

glm::vec2 Mouse::getPos()
{
	return glm::vec2((float)getPosX(), (float)getPosY());
}

bool Mouse::isLeftDown()
{
	return m_pBtnEvent->button == 1;
}

bool Mouse::isLeftClicked() 
{
	return m_pBtnEvent->clicks == 1 && m_pBtnEvent->button == 1;
}