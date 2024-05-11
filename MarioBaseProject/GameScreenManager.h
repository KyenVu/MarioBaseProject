#pragma once
#ifdef _GameScreenManager.h
#define _GameScreenManager_h
#endif // _GameScreenManager.h

#include <SDL.h>
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "Commons.h"

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

