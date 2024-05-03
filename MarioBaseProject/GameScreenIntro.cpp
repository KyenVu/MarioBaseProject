#include "GameScreenIntro.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer), m_manager(manager)
{
    SetUpLevel();
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
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
    // Check for key press event to switch screens
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_RETURN)
        {
            // Switch to level screen
            m_manager->ChangeScreen(SCREEN_LEVEL1);
        }
    }
}

bool GameScreenIntro::SetUpLevel()
{
    //create background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/garnacho.bmp")) {
        cout << "Failed to load background texture!" << endl;
        return false;
    }

    return true;
}
