#ifndef PIPE_H
#define PIPE_H

#include "Texture2D.h"
#include "Commons.h"

class Pipe {
public:
    Pipe(SDL_Renderer* renderer, Vector2D position, bool isTop);
    ~Pipe();

    void Render();
    void Update(float deltaTime, SDL_Event e);
    SDL_Rect GetCollisionBox();

private:
    SDL_Renderer* m_renderer;
    Vector2D m_position;
    Texture2D* m_texture;
    SDL_Rect m_collision_box;

    bool m_is_top;
};

#endif // PIPE_H
