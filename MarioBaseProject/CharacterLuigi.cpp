#include "CharacterLuigi.h"
#include "Texture2D.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_Position)
    :Character(renderer, imagePath, start_Position)
{}

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
		AddGravity(deltaTime);
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
