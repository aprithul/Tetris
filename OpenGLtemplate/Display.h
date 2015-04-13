#pragma once

#include <SDL2\SDL.h>

class Display
{
public:
	Display(int x, int y, int width, int height, SDL_Window* window);
	~Display();
};

