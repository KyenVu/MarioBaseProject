#include "Pipe.h"

Pipe::Pipe(SDL_Renderer* renderer, Vector2D position, bool isTop) : m_renderer(renderer), m_position(position), m_isTop(isTop) {
    m_texture = new Texture2D(renderer);
    if (isTop) {
        m_texture->LoadFromFile("Images/TopPipe.png");
    }
    else {
        m_texture->LoadFromFile("Images/BottomPipe.png");
    }
    m_verticalSpeed = 0.5f; // Speed of vertical movement
    m_horizontalSpeed = 100.0f; // Speed of horizontal movement
    m_maxVerticalDisplacement = 30.0f; // Max displacement from initial position
    m_initialY = position.y;
}

Pipe::~Pipe() {
    delete m_texture;
}

void Pipe::Render() {
    m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Pipe::Update(float deltaTime, SDL_Event e) {
    // Update vertical position for oscillation
    m_position.y = m_initialY + m_maxVerticalDisplacement * sin(SDL_GetTicks() / 1000.0f);

    // Update horizontal position
    m_position.x -= m_horizontalSpeed * deltaTime;
}

SDL_Rect Pipe::GetCollisionBox() {
    return { (int)m_position.x, (int)m_position.y, m_texture->GetWidth(), m_texture->GetHeight() };
}
