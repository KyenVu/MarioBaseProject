#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);

	m_texture->LoadFromFile(imagePath);
	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left) 
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
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
		default:
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
		default:
			break;
		}
		break;
	}
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}