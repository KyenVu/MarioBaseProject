#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"

using namespace std;

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

bool InitSDL();
void CloseSDL();

bool Update()
{
    // Event handler
    SDL_Event e;

    // Poll SDL for any events
    SDL_PollEvent(&e);

    // Handle the events
    switch (e.type)
    {
        // Click the 'X' to quit
    case SDL_QUIT:
        return true;
        break;
    }

    return false;
}

int main(int argc, char* args[])
{
    // Flag to check if we wish to quit
    bool quit = false;

    // Initialize SDL and check
    if (!InitSDL())
    {
        return 1; // Exit the program if SDL initialization fails
    }

    // Game Loop
    while (!quit)
    {
        quit = Update();
    }

    // Close SDL before ending the program
    CloseSDL();
    return 0;
}

// Function prototypes
bool InitSDL()
{
    // Set up SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialise. Error: " << SDL_GetError();
        return false;
    }
    else
    {
        // set up passed so create window
        g_window = SDL_CreateWindow("Games Engine Creation",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        // did the window get created ?
        if (g_window == nullptr)
        {
            // window failed
            cout << "Window was not created. Error : " << SDL_GetError();
            return false;
        }
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer != nullptr)
    {
        //init PNG loading
        int imageFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imageFlags) & imageFlags))
        {
            cout << "SDL_Image could not initialize. Error: " << IMG_GetError();
            return false;
        }
    }
    else
    {
        cout << "Render could not initialize. Error: " << IMG_GetError();
        return false;
    }

    if (g_renderer != nullptr)
    {
        //init PNG loading
        int imageFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imageFlags) & imageFlags))
        {
            cout << "SDL_Image could not initialize. Error: " << IMG_GetError();
            return false;

        }
    }

    return true; // Return true if SDL initialization is successful
}

void Render()
{
    //Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(g_renderer);

    //Set where to render the texture
    SDL_Rect renderLocation = { 0,0, SCREEN_HEIGHT, SCREEN_WIDTH };

    //Render to screen
    SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

    
}

void CloseSDL()
{
    // release the window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;
    // quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
