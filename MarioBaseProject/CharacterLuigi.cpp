#include "CharacterLuigi.h"
#include "Texture2D.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_Position)
    :Character(renderer, imagePath, start_Position)
{}

CharacterLuigi::~CharacterLuigi() {}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
    Character::Update(deltaTime, e);
}
