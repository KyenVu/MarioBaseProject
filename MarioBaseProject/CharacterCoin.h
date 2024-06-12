#pragma once
#include "Character.h"
#include "Texture2D.h"

class CharacterCoin : public Character
{
public:  CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
      ~CharacterCoin();

      void Update(float deltaTime, SDL_Event e) override;
      void Render() override;

private:
    float m_frame_delay;
    int m_current_frame;
    const float ANIMATION_DELAY = 0.10f; // Adjust as needed
protected:
    float m_single_sprite_w;
    float m_single_sprite_h;
};

