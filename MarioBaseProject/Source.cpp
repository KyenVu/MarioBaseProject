#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialise. Error: " << SDL_GetError();
        return false;
    }

    g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
    if (g_window == nullptr)
    {
        cout << "Window was not created. Error : " << SDL_GetError();
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == nullptr)
    {
        cout << "Renderer could not be created. Error: " << SDL_GetError();
        return false;
    }

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
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

    Uint32 new_time = SDL_GetTicks();
    float deltaTime = (float)(new_time - g_old_time) / 1000.0f;
    g_old_time = new_time;

    game_screen_manager->Update(deltaTime, e);

    return false;
}

int main(int argc, char* args[])
{
    if (InitSDL())
    {
        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
        // set the time
        g_old_time = SDL_GetTicks();

        bool quit = false;
        while (!quit)
        {
            Render();
            quit = Update();
        }

        CloseSDL();
        return 0;
    }

    return -1; // initialization failed
}