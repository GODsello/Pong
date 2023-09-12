#pragma once

#include <SDL.h>
#include <stdio.h>

class Window
{
public:
	Window();
	~Window();
	
	bool Init(const char* title, const int width, const int height);
	void CleanUp();

	SDL_Window* GetWindow() { return window; }
	SDL_Renderer* GetRenderer() { return renderer; };

private:
	int width, height;
	const char* title;

	SDL_Window *window;
	SDL_Renderer* renderer;
};

