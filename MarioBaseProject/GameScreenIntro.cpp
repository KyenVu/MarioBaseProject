#include "GameScreenIntro.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <iostream>
using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
    if (!SetUpLevel()) {
        cout << "Failed to set up intro screen!" << endl;
    }
}

GameScreenIntro::~GameScreenIntro()
{
    // Release resources
    delete m_background_texture;
    m_background_texture = nullptr;
}

void GameScreenIntro::Render()
{
    // Draw background
    if (m_background_texture != nullptr) {
        m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
    }
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
    // Check for key press event to switch screens
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_RETURN) {
            // Switch to level screen
            GameScreenManager->ChangeScreen(SCREENS::SCREEN_INTRO);
        }
    }
}

bool GameScreenIntro::SetUpLevel()
{
    // Create background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/title_background.bmp")) {
        cout << "Failed to load intro screen background texture!" << endl;
        return false;
    }

    return true;
}
