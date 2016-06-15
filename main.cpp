#include "glew.h"
#include "SDL.h"
#include "Display.h"
#include "Game.h"
#include "Input\Keyboard.h"
#include "Input\Mouse.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Keyboard* Keyboard::_INSTANCE = NULL;
Mouse* Mouse::_INSTANCE = NULL;

int main(int argc, char* argv[]) {
	Display display(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Application");

	Game game;
	game.Init(display);

	while (!display.isClosed())
	{
		SDL_Event e;
		display.Update();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				display.Close();
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				Keyboard::getInstance()->ProcessSDLEvent(e);
			else if (e.type == SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP || SDL_MOUSEMOTION)
				Mouse::getInstance()->ProcessSDLEvent(e);
		}
		
		game.Update();
		game.Draw();
	}

	return 0;
}