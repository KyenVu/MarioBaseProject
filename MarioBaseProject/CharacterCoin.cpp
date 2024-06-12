#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map)
 : Character(renderer, imagePath, start_position, map) 
{
    m_frame_delay = ANIMATION_DELAY;
    m_current_frame = 0;
    m_single_sprite_w = m_texture->GetWidth() / 3; // 3 sprites in the sheet
    m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
    m_frame_delay -= deltaTime;
    if (m_frame_delay <= 0.0f) 
    {
        m_frame_delay = ANIMATION_DELAY;
        m_current_frame++;
        if (m_current_frame > 2) 
        {
            m_current_frame = 0;
        }
    }
}

void CharacterCoin::Render()
{
    int left = m_single_sprite_w * m_current_frame;

    SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

    SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

    m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}
