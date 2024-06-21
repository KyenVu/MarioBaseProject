#include "CharacterBird.h"
#include "Texture2D.h"

CharacterBird::CharacterBird(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
    : m_renderer(renderer), m_position(start_position), m_is_jumping(false), m_jump_force(0.0f), m_gravity(100.0f)
{
    m_texture = new Texture2D(renderer);
    m_texture->LoadFromFile(imagePath);
    m_collision_box = { (int)m_position.x, (int)m_position.y, m_texture->GetWidth(), m_texture->GetHeight() };
}

CharacterBird::~CharacterBird()
{
    delete m_texture;
    m_texture = nullptr;
}

void CharacterBird::Render()
{
    m_texture->Render(m_position, SDL_FLIP_NONE);
}

void CharacterBird::Update(float deltaTime, SDL_Event e)
{
    if (m_is_jumping)
    {
        m_position.y -= m_jump_force * deltaTime;
        m_jump_force -= m_gravity * deltaTime;
        if (m_jump_force <= 0.0f)
        {
            m_is_jumping = false;
        }
    }
    else
    {
        m_position.y += m_gravity * deltaTime;
    }

    // Update collision box
    m_collision_box.x = (int)m_position.x;
    m_collision_box.y = (int)m_position.y;

    // Handle input for jumping
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_SPACE)
        {
            Jump();
        }
    }
}

void CharacterBird::Jump()
{
    
        m_is_jumping = true;
        m_jump_force = FLAPPY_JUMP_FORCE; 

}

void CharacterBird::FallOffMap(float deltaTime, float groundLevel)
{
    m_position.y += 300.0f * deltaTime; // Adjust the falling speed as needed

    // Check if the bird has hit the ground
    if (m_position.y + m_texture->GetHeight() >= groundLevel)
    {
        m_position.y = groundLevel - m_texture->GetHeight();
    }
}

SDL_Rect CharacterBird::GetCollisionBox()
{
    return m_collision_box;
}

