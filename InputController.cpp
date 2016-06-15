#include "InputController.h"

InputController::InputController()
{
	m_actionMap["Escape"] = SDLK_ESCAPE;
	m_pKBStateOld = nullptr;
	m_pKBState = nullptr;
}


InputController::~InputController()
{
	m_actionMap.clear();
	m_pMouse->clear();
	delete m_pMouse;
	delete m_pKeyboard;
	m_pKeyboard = nullptr;
	m_pMouse = nullptr;
}

void InputController::Update()
{
	SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
	m_pKeyboard = Keyboard::getInstance();
	m_pMouse = Mouse::getInstance();
	m_pKBStateOld.reset();
	m_pKBStateOld = std::move(m_pKBState);
	m_pKBState.reset(m_pKeyboard->GetState());
}

glm::vec2 InputController::GetMousePos() {
	return m_pMouse->getPos();
}

Mouse* InputController::GetMouse()
{
	return m_pMouse;
}

bool InputController::isButtonDown(string ActionName)
{
	return (m_pKBState) &&
		m_pKBState->IsKeyDown(m_actionMap[ActionName]);
}

bool InputController::isButtonHit(string ActionName)
{
	return (m_pKBStateOld && m_pKBState) &&
		m_pKBStateOld->IsKeyDown(m_actionMap[ActionName]) &&
		m_pKBState->IsKeyUp(m_actionMap[ActionName]);
}

bool InputController::SetKey(string ActionName, int Key)
{
	if (m_actionMap[ActionName])
		return false;

	m_actionMap[ActionName] = Key;
	return true;
}