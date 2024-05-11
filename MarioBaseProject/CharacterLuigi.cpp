#include "CharacterLuigi.h"
#include "Texture2D.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
	: Character(renderer, imagePath, start_position, map) {}

CharacterLuigi::~CharacterLuigi() {}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	if (m_jumping)
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
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
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_w:
			Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			m_moving_right = false;
			break;
		case SDLK_a:
			m_moving_left = false;
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
void CharacterLuigi::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
}
