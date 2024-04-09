//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"

using namespace std;

// Globals
SDL_Window* g_window = nullptr;

bool InitSDL();
void CLoseSDL();

int main(int argc, char* args[])
{
	// check if sdl was set up correctly
		if(InitSDL())
	{
		SDL_Delay(5000);
	}
	CLoseSDL();
	return 0;
}
// Function prototypes
bool InitSDL()
{
	// Set up SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL di d not i ni t i al i se. Er r or : " << SDL_GetError ();
		return false;
	}
		else
	{
		// set up passed so cr eat e window
		g_window = SDL_CreateWindow("Games Engine Creation",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
		// di d t he wi ndow get cr eat ed ?
			if(g_window == nullptr)
		{
			//windowfailed
			cout << "Window was not created. Error : " << SDL_GetError ();
			return false;
		}
	}
}
void CLoseSDL()
{
	// release the window
		SDL_DestroyWindow(g_window);
	g_window = nullptr;
	// quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
}