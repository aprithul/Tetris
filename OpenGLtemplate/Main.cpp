#include "Main.h"
#include <GL\glew.h>
#include <SDL2\SDL.h>

// function prototype
void init();


SDL_Window* window;
SDL_Event event;
bool isRunning;


int main(int args, char* argv[])
{

	init();
	

	// game loop
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)	// quit on window crossed
				isRunning = false;
		}
	}



	return 0;
}



void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	isRunning = true;

}