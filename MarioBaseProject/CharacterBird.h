#ifndef CHARACTER_BIRD_H
#define CHARACTER_BIRD_H

#include "Commons.h"
#include "Texture2D.h"
#include "constants.h"
#include <SDL.h>
#include <string>

class CharacterBird {
public:
    CharacterBird(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
    ~CharacterBird();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    void Jump();

    void FallOffMap(float deltaTime, float groundLevel);

    SDL_Rect GetCollisionBox();
    Vector2D GetPosition() const { return m_position; }
    Vector2D SetPosition() const { return m_position; }


private:
    SDL_Renderer* m_renderer;
    Vector2D m_position;
    Texture2D* m_texture;
    SDL_Rect m_collision_box;

    float m_jump_force;
    float m_gravity = FLAPPY_GRAVITY;
    bool m_is_jumping;

};

#endif // CHARACTER_BIRD_H
