#include "GameScreenIntro.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>


using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer), m_manager(manager)
{
    SetUpLevel();

    m_font = TTF_OpenFont("PIXEARG_.ttf", 22);
    if (!m_font)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

GameScreenIntro::~GameScreenIntro()
{
    delete m_background_texture;
    m_background_texture = nullptr;
}

void GameScreenIntro::Render()
{
    // Draw background
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
    SDL_Color yellow = { 196, 180, 84, 255 };
    RenderText("Game Engine Creation", yellow, 100, 100);
    RenderText("1. Mario Game", yellow, 100, 150);
    RenderText("2. Flappy Bird Game", yellow, 100, 200);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_1:
            m_manager->ChangeScreen(SCREEN_LEVEL1);
            break;
        case SDLK_2:
            m_manager->ChangeScreen(FLAPPY_BIRD_SCREEN);
            break;
        default:
            break;
        }
    }

}

bool GameScreenIntro::SetUpLevel()
{
    //create background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/IntroBackGround.png")) 
    {
        cout << "Failed to load background texture!" << endl;
        return false;
    }

    return true;
}
void GameScreenIntro::RenderText(const std::string& message, SDL_Color color, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_FreeSurface(surface);

    SDL_RenderCopy(m_renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}
