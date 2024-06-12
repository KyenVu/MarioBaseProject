#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenIntro.h"
#include "FlappyBirdScreen.h"
#include <iostream>
using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) : m_renderer(renderer), m_current_screen(nullptr) 
{
    ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() 
{
    delete m_current_screen;
    m_current_screen = nullptr;
}

void GameScreenManager::Render() 
{
    if (m_current_screen != nullptr) 
    {
        m_current_screen->Render();
    }
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) 
{
    if (m_current_screen != nullptr) 
    {
        m_current_screen->Update(deltaTime, e);
    }
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) 
{
    // delete current screen
    if (m_current_screen != nullptr) 
    {
        delete m_current_screen;
    }

    // create new screen
    switch (new_screen) 
    {
    case SCREEN_LEVEL1:
        tempScreen = new GameScreenLevel1(m_renderer);
        m_current_screen = (GameScreen*) tempScreen;
        tempScreen = nullptr;
        // add new screen
        break;
    case SCREEN_INTRO:
        tempScreen = new GameScreenIntro(m_renderer, this);
        m_current_screen = (GameScreen*)tempScreen;
        tempScreen = nullptr;
        break;
    case FLAPPY_BIRD_SCREEN:
        tempScreen = new FlappyBirdScreen(m_renderer, this);
        m_current_screen = (GameScreen*)tempScreen;
        tempScreen = nullptr;
        break;

    default:
        cout << "Invalid screen type!" << endl;
        break;
    }
}


    