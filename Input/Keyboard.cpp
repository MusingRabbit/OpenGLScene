#include "Keyboard.h"

Keyboard::Keyboard()
{
	KeyList = vector<int>();
}

Keyboard::~Keyboard()
{
	KeyList.clear();
}

Keyboard::Keyboard(const Keyboard& value)
{
	KeyList = value.KeyList;
}

Keyboard::Keyboard(Keyboard&& value)
{
	KeyList = value.KeyList;
}

void Keyboard::ProcessSDLEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN) 
	{
		for (vector<int>::iterator i = KeyList.begin(); i < KeyList.end(); i++)
		{
			if (*i == e.key.keysym.sym) {
				return;
			}
		}
		KeyList.push_back(e.key.keysym.sym);
	}
	else if (e.type == SDL_KEYUP) 
	{
		for (vector<int>::iterator i = KeyList.begin(); i < KeyList.end(); i++)
		{
			if (*i == e.key.keysym.sym)
			{
				KeyList.erase(i);
				break;
			}
		}
	}
}

KeyboardState* Keyboard::GetState()
{
	return new KeyboardState(KeyList);
}

vector<int> Keyboard::GetPressedKeys()
{
	return KeyList;
}