#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <glew.h>
#include <iostream>
#include "SDL.h"
#include <glm.hpp>

class Display
{
public:
	Display(int width, int height, const std::string& title) {
		Init(width, height, title);
	}

	inline virtual ~Display() {
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	inline void Init(int width, int height, const std::string& title) {
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		m_iHeight = height;
		m_iWidth = width;
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iWidth, m_iHeight, SDL_WINDOW_OPENGL);
		m_glContext = SDL_GL_CreateContext(m_window);

		m_bClosed = false;
	}

	inline void Update() {
		SDL_GL_SwapWindow(m_window);
	}

	inline void Clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	inline void Close() {
		m_bClosed = true;
	}

	inline bool isClosed() {
		return m_bClosed;
	}

	inline int GetWidth() {
		return m_iWidth;
	}

	inline int GetHeight() {
		return m_iHeight;
	}

	inline float getAspectf() {
		return (float)m_iWidth / (float)m_iHeight;
	}

private:
	Display(const Display& rhs) {}
	Display& operator = (const Display& rhs) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_bClosed;
	int m_iWidth, m_iHeight;
	int m_iMouseX, m_iMouseY;
};
#endif // !DISPLAY_H
