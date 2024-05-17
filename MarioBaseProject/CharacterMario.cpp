#include "CharacterMario.h"
#include "Texture2D.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
               :Character(renderer, imagePath, start_position, map) {}

CharacterMario::~CharacterMario() {}

void CharacterMario::Update(float deltaTime, SDL_Event e) 
{
	if (m_jumping)
	{
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		m_position.y -= m_jump_force * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}
	else
	{
		//collision position variable
		int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WITDH;
		int foot_position = (int)(m_position.y + (m_texture->GetHeight())) / TILE_HEIGHT;
		if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
		{
			AddGravity(deltaTime);
		}
		else
		{
			//collided with ground so we can jump again
			m_can_jump = true;
		}
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_UP:
			Jump();
			break;
		}

		break;
	}
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}