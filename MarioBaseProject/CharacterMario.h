#pragma once
#include "Character.h"

using namespace std;

class CharacterMario : public Character
{
public:
    CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_Position);
    ~CharacterMario();
    void Update(float deltaTime, SDL_Event e) override;
};

