#include "Collisions.h"
//initialise instance to nullptr 
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (m_instance)
	{
		m_instance = new Collisions;
	}
	return m_instance;
}
bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D(character1->GetPosition().x - character2->GetPosition().x,
							character1->GetPosition().y - character2->GetPosition().y);

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combined_distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	return distance < combined_distance;
}