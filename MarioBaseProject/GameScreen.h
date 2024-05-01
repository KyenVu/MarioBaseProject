#pragma once
#ifndef _GameScreen.h
#endif // !_GameScreen.h

#include <SDL.h>
class GameScreen 
{
protected:
    SDL_Renderer* m_renderer;

public:
    GameScreen(SDL_Renderer* renderer);
    virtual ~GameScreen();

    virtual void Render();
    virtual void Update(float deltaTime, SDL_Event e);
};