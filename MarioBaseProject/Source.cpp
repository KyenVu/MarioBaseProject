#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "constants.h"
#include "GameScreenManager.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager = nullptr;
Uint32 g_old_time;

bool InitSDL() 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() < 0) 
    {
        cout << "Text could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Create window
    g_window = SDL_CreateWindow("Mario Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (g_window == nullptr) 
    {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Create renderer
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == nullptr) 
    {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void CloseSDL()
{
    // destroy game screen manager
    delete game_screen_manager;
    game_screen_manager = nullptr;

    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    SDL_Quit();
}

void Render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_renderer);

    game_screen_manager->Render();

    // Update the screen
    SDL_RenderPresent(g_renderer);
}

bool Update()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT)
    {
        return true;
    }

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_1:
            game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
            break;
        case SDLK_2:
            game_screen_manager->ChangeScreen(FLAPPY_BIRD_SCREEN);
            break;
        default:
            break;
        }
    }

    Uint32 new_time = SDL_GetTicks();
    float deltaTime = (float)(new_time - g_old_time) / 1000.0f;
    g_old_time = new_time;

    game_screen_manager->Update(deltaTime, e);

    return false;
}

int main(int argc, char* args[]) 
{
    if (!InitSDL()) 
    {
        return -1;
    }

    // Create the GameScreenManager instance
    game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO);

    g_old_time = SDL_GetTicks();

    // Main loop
    bool quit = false;

    SDL_Event e;

    while (!quit) 
    {
        // Update and render
        quit = Update();
        Render();
    }

    // Clean up
    CloseSDL();
    delete game_screen_manager;
    game_screen_manager = nullptr;

    return 0;
}