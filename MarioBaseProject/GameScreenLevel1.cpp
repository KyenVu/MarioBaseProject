#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) 
{
    SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1() 
{
    delete m_background_texture;
    m_background_texture = nullptr;
    delete mario;
    mario = nullptr;
    delete luigi;
    luigi = nullptr;
}

void GameScreenLevel1::Render() 
{
    // draw background
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
    mario->Render();
    luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
    //update character
    mario->Update(deltaTime, e);
    luigi->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel() 
{
    //create background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/test.bmp")) 
    {
        cout << "Failed to load background texture!" << endl;
        return false;
    }
    mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
    luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330));
    return true;
}
