#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constants.h"
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;

class LevelMap;
class Texture2D;
class Character 
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);

	inline bool IsJumping()
	{
		return m_jumping;
	}

	inline void CancleJump()
	{
		m_jumping = false;
	}

	float GetCollisionRadius();
	Rect2D GetFeetCollisionBox();
	Vector2D GetPosition();

	inline Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y,
		m_texture->GetWidth(), m_texture->GetHeight());
	}

	void Bounce();

	inline bool GetAlive() { return m_alive; }

	void SetAlive(bool IsAlive) { m_alive = IsAlive; }

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	LevelMap* m_current_level_map;


	bool m_jumping;
	bool m_can_jump;
	bool m_moving_left;
	bool m_moving_right;
	bool m_alive;

	float m_jump_force;
	float m_collision_radius;	

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

private:
};

