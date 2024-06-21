#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>
#include <SDL_ttf.h>

class GameScreenIntro : public GameScreen
{
public:
    GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* manager);
    ~GameScreenIntro();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;

private:
    Texture2D* m_background_texture;
    GameScreenManager* m_manager;
    TTF_Font* m_font;

    bool SetUpLevel();
    void RenderText(const std::string& message, SDL_Color color, int x, int y);
};
