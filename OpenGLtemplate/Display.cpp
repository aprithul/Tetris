#include "Display.h"
#include <GL\glew.h>


Display::Display(int x, int y, int height, int width, SDL_Window* window)
{
	//init window
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	// init opengl

	

	







}


Display::~Display()
{
}
