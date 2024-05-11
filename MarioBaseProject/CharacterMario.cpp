#include "CharacterMario.h"
#include "Texture2D.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
               :Character(renderer, imagePath, start_position, map) {}

CharacterMario::~CharacterMario() {}

void CharacterMario::Update(float deltaTime, SDL_Event e) 
{
    Character::Update(deltaTime, e);
}