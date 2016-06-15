#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>
#include <memory>
#include <glm.hpp>
#include "SDL.h"
#include "Input\Keyboard.h"
#include "Input\Mouse.h"
using namespace std;

class InputController
{
public:
	InputController();
	~InputController();

	void Update();
	bool isButtonDown(string ActionName);
	bool isButtonHit(string ActionName);
	bool SetKey(string ActionName, int Key);
	glm::vec2 GetMousePos();
	Mouse* GetMouse();
private:
	unique_ptr<KeyboardState> m_pKBState;
	unique_ptr<KeyboardState> m_pKBStateOld;
	unordered_map<string, Uint32> m_actionMap;
	Keyboard *m_pKeyboard;
	Mouse *m_pMouse;
	int m_iMouseX, m_iMouseY;
};

