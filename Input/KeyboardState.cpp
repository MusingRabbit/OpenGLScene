#include "KeyboardState.h"

//Constructor
KeyboardState::KeyboardState()
{
	m_pKeyBuffer = new bool[_BUFFERSIZE]();
}

//Copy Constructor
KeyboardState::KeyboardState(const KeyboardState& other)
{
	m_pKeyBuffer = new bool[_BUFFERSIZE]();

	for (int i = 0; i<_BUFFERSIZE; i++)
		m_pKeyBuffer[i] = other.m_pKeyBuffer[i];
}

//Move Constructor
KeyboardState::KeyboardState(KeyboardState&& other)
	:m_pKeyBuffer(other.m_pKeyBuffer)
{
	other.m_pKeyBuffer = nullptr;
}


KeyboardState::KeyboardState(vector<int> Keys)
{
	m_pKeyBuffer = new bool[_BUFFERSIZE]();
	SetPressedKeys(Keys);
}

//Deconstructor
KeyboardState::~KeyboardState(void)
{
	if (m_pKeyBuffer)
		delete m_pKeyBuffer;

	m_pKeyBuffer = nullptr;
}

KeyboardState& KeyboardState::operator = (KeyboardState &&rVal)
{
	if (this != &rVal)
	{
		if (m_pKeyBuffer)
			delete m_pKeyBuffer;

		m_pKeyBuffer = rVal.m_pKeyBuffer;
		rVal.m_pKeyBuffer = nullptr;
	}

	return *this;
}

KeyboardState& KeyboardState::operator = (const KeyboardState &rVal)
{
	if (this != &rVal)
	{
		if (m_pKeyBuffer)
			delete m_pKeyBuffer;

		m_pKeyBuffer = nullptr;
		m_pKeyBuffer = new bool[rVal._BUFFERSIZE]();
		copy(rVal.m_pKeyBuffer, rVal.m_pKeyBuffer + _BUFFERSIZE, m_pKeyBuffer);
	}

	return *this;
}

bool KeyboardState::IsKeyDown(int key)
{
	return  (key < _BUFFERSIZE) && m_pKeyBuffer[key];
}
bool KeyboardState::IsKeyUp(int key)
{
	return   (key < _BUFFERSIZE) && (!m_pKeyBuffer[key]);
}

void KeyboardState::SetPressedKeys(vector<int> Keys)
{
	int iKeys = Keys.size();

	for (int i = 0; i < iKeys; i++) {
		if (Keys[i] < _BUFFERSIZE)
			m_pKeyBuffer[Keys[i]] = true;
	}
}