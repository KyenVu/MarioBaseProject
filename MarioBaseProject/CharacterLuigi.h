#pragma once
#include "Character.h"
class CharacterLuigi : public Character
{
public:
    CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_Position, LevelMap* map);
    ~CharacterLuigi();
    void Update(float deltaTime, SDL_Event e) override;
    void Render();
};

