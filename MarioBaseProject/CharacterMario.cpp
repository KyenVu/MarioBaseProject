#include "CharacterMario.h"
#include "Texture2D.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_Position) 
    :Character(renderer, imagePath, start_Position)
{}

CharacterMario::~CharacterMario() {}

void CharacterMario::Update(float deltaTime, SDL_Event e) 
{
    Character::Update(deltaTime, e);
}