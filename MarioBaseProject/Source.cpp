#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "constants.h"

using namespace std;

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);

bool InitSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialise. Error: " << SDL_GetError();
        return false;
    }

    // Create window
    g_window = SDL_CreateWindow("Games Engine Creation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    if (g_window == nullptr)
    {
        cout << "Window was not created. Error : " << SDL_GetError();
        return false;
    }

    // Create renderer
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == nullptr)
    {
        cout << "Renderer could not be created. Error: " << SDL_GetError();
        return false;
    }

    // Initialize PNG loading
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags))
    {
        cout << "SDL_Image could not initialize. Error: " << IMG_GetError();
        return false;
    }

    // Load the texture
    g_texture = new Texture2D(g_renderer);

    if (!g_texture->LoadFromFile("Images/test.bmp"))
    {
        cout << "sahdsad";
        return false;
    }

    return true;
}

void CloseSDL()
{
    // Release the texture
    delete g_texture;
    g_texture = nullptr;

    // Destroy renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

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

void Render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);

    g_texture->Render(Vector2D(), SDL_FLIP_NONE);

    // Update the screen
    SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        cout << "Unable to load image " << path << ". SDL_image Error: " << IMG_GetError();
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
        if (newTexture == nullptr)
        {
            cout << "Unable to create texture from " << path << ". SDL Error: " << SDL_GetError();
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(p_surface);
    }

    return newTexture;
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
        Render(); // Render texture to screen
        quit = Update(); // Check for quit event
    }

    // Close SDL before ending the program
    CloseSDL();

    return 0;
}
