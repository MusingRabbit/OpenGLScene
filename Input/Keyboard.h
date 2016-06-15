#pragma once
#include <vector>
#include <iostream>
#include "SDL.h"
#include "KeyboardState.h"


using namespace std;

class Keyboard
{
public:
	//Copy Constructor
	Keyboard(const Keyboard& rhs);
	//Move Constructor
	Keyboard(Keyboard&& other);
	//Default Constructor
	Keyboard();
	//Deconstructor
	~Keyboard();

	vector<int> KeyList;

	static Keyboard* getInstance()
	{
		if (!_INSTANCE)
			_INSTANCE = new Keyboard();

		return _INSTANCE;
	}

	void ProcessSDLEvent(SDL_Event& e);

	KeyboardState* GetState();

private:
	vector<int> GetPressedKeys();
	static Keyboard* _INSTANCE;
};