#include "GameScreen.h"	
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}
void GameScreen::Render() {};
void GameScreen::Update(float deltaTime, SDL_Event e) {};

