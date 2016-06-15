#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;


class KeyboardState
{
public:

	//Copy Constructor
	KeyboardState(const KeyboardState& rhs);
	//Move Constructor
	KeyboardState(KeyboardState&& other);
	//
	KeyboardState(vector<int> Keys);
	//Default Constructor
	KeyboardState();
	//Deconstructor
	~KeyboardState();

	bool IsKeyDown(int Key);
	bool IsKeyUp(int Key);
	void SetPressedKeys(vector<int> Keys);


	KeyboardState& operator = (const KeyboardState &rVal);
	KeyboardState& operator = (KeyboardState &&rVal);

private:
	static const int _BUFFERSIZE = 512;
	bool* m_pKeyBuffer;
};


#endif