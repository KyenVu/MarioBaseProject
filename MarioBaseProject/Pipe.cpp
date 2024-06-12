#include "Pipe.h"
#include "Texture2D.h"

Pipe::Pipe(SDL_Renderer* renderer, Vector2D position, bool isTop)
    : m_renderer(renderer), m_position(position), m_is_top(isTop)
{
    m_texture = new Texture2D(renderer);
    m_texture->LoadFromFile("Images/Pipe.png");
    m_collision_box = { (int)m_position.x, (int)m_position.y, m_texture->GetWidth(), m_texture->GetHeight() };
}

Pipe::~Pipe()
{
    delete m_texture;
    m_texture = nullptr;
}

void Pipe::Render()
{
    m_texture->Render(m_position, m_is_top ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
}

void Pipe::Update(float deltaTime, SDL_Event e)
{
    m_position.x -= 200.0f * deltaTime; //pipe speed
    m_collision_box.x = (int)m_position.x;

    // Remove pipe if it goes off screen
    if (m_position.x + m_texture->GetWidth() < 0)
    {
        m_position.x = 800; // Reset position for reuse, or handle deletion
    }
}

SDL_Rect Pipe::GetCollisionBox()
{
    return m_collision_box;
}
