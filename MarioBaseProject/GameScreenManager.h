#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "GameScreenLevel1.h"
enum SCREENS
{
    SCREEN_INTRO,
    SCREEN_MENU,
    SCREEN_LEVEL1,
    SCREEN_LEVEL2,
    SCREEN_GAMEOVER,
    SCREEN_HIGHSCORES
};
class GameScreenManager 
{
private:
    SDL_Renderer* m_renderer;
    GameScreen* m_current_screen;
    GameScreen* tempScreen;

public:
    GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
    ~GameScreenManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);
    void ChangeScreen(SCREENS new_screen);
};

