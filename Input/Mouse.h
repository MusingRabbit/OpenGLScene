#pragma once
#include <vector>
#include <iostream>
#include "SDL.h"
#include "glm.hpp"

class Mouse
{
public:
	Mouse(const Mouse& rhs);
	Mouse(Mouse&& rhs);
	Mouse();
	~Mouse();

	static Mouse* getInstance()
	{
		if (!_INSTANCE)
			_INSTANCE = new Mouse();

		return _INSTANCE;
	}


	int getPosX();
	int getPosY();
	bool isLeftDown();
	bool isLeftClicked();
	bool isLeftDoubleClicked();
	glm::vec2 getPos();

	void ProcessSDLEvent(SDL_Event& e);
	void clear();
private : 
	static Mouse* _INSTANCE;
	void init();

	SDL_MouseButtonEvent* m_pBtnEvent;
	SDL_MouseWheelEvent* m_pWheelEvent;
	SDL_MouseMotionEvent* m_pMotionEvent;

};

