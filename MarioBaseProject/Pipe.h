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
    void SetScored(bool scored) { m_scored = scored; }
    bool HasScored() const { return m_scored; }

    SDL_Rect GetCollisionBox();
    Vector2D GetPosition() const { return m_position; }

private:
    Texture2D* m_texture;
    Vector2D m_position;
    SDL_Renderer* m_renderer;

    bool m_isTop;
    bool m_scored;
    float m_verticalSpeed;
    float m_horizontalSpeed;
    float m_maxVerticalDisplacement;
    float m_initialY;

};

#endif // PIPE_H
