#include "FlappyBirdScreen.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

FlappyBirdScreen::FlappyBirdScreen(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer)
{
    SetUpLevel();
}

FlappyBirdScreen::~FlappyBirdScreen()
{
    delete m_background_texture;
    delete m_bird;
    for (Pipe* pipe : m_pipes)
    {
        delete pipe;
    }
    m_pipes.clear();
}

void FlappyBirdScreen::SetUpLevel()
{
    m_background_texture = new Texture2D(m_renderer);
    m_background_texture->LoadFromFile("Images/FlappyBackground.png");

    m_bird = new CharacterBird(m_renderer, "Images/FlappyBird.png", Vector2D(100, 300));

    m_pipe_spawn_timer = 0.0f;
    m_ground_level = 416.0f - 34; // Adjust ground level as needed
}

void FlappyBirdScreen::Render()
{
    m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
    m_bird->Render();
    for (Pipe* pipe : m_pipes)
    {
        pipe->Render();
    }
}

void FlappyBirdScreen::Update(float deltaTime, SDL_Event e)
{
    m_bird->Update(deltaTime, e);
    m_pipe_spawn_timer -= deltaTime;
    if (m_pipe_spawn_timer <= 0.0f)
    {
        float pipe_y = (rand() % 300) + 200; // Random height
        m_pipes.push_back(new Pipe(m_renderer, Vector2D(512, pipe_y),true)); 
        m_pipe_spawn_timer = 2.0f; // Spawn pipe every 2 seconds
    }

    for (auto pipe : m_pipes)
    {
        pipe->Update(deltaTime, e);
    }

    // Remove pipes that have gone off-screen
    m_pipes.erase(std::remove_if(m_pipes.begin(), m_pipes.end(), [](Pipe* pipe) {
        bool offScreen = pipe->GetCollisionBox().x + pipe->GetCollisionBox().w < 0;
        if (offScreen) delete pipe;
        return offScreen;
        }), m_pipes.end());

    CheckCollisions();
}

void FlappyBirdScreen::CreatePipe()
{
    int gap_y = rand() % 216 + 50; // Randomize pipe gap position
    Pipe* topPipe = new Pipe(m_renderer, Vector2D(512, gap_y - 300), true);
    Pipe* bottomPipe = new Pipe(m_renderer, Vector2D(512, gap_y + 100),false);

    m_pipes.push_back(topPipe);
    m_pipes.push_back(bottomPipe);
}

void FlappyBirdScreen::CheckCollisions()
{
    SDL_Rect birdBox = m_bird->GetCollisionBox();

    for (Pipe* pipe : m_pipes)
    {
        SDL_Rect pipeBox = pipe->GetCollisionBox();

        // Convert SDL_Rect to Rect2D
        Rect2D birdRect(birdBox.x, birdBox.y, birdBox.w, birdBox.h);
        Rect2D pipeRect(pipeBox.x, pipeBox.y, pipeBox.w, pipeBox.h);

        if (Collisions::Instance()->Box(birdRect, pipeRect))
        {
            std::cout << "Collision detected!" << std::endl;
            // Handle collision
        }
    }

    if (birdBox.y + birdBox.h >= m_ground_level)
    {
        std::cout << "Bird hit the ground!" << std::endl;
        // Handle collision
    }
}
