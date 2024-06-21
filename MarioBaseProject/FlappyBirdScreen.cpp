#include "FlappyBirdScreen.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

FlappyBirdScreen::FlappyBirdScreen(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer) {
    SetUpLevel();

    m_score = 0;

    // Load font
    m_font = TTF_OpenFont("PIXEARG_.ttf", 28);
    if (!m_font) 
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    // Create initial score texture
    SDL_Color color = { 255, 255, 255, 255 }; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, "Score: 0", color);
    m_scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Set score texture position and size
    m_scoreRect = { 10, 10, surface->w, surface->h };

}

FlappyBirdScreen::~FlappyBirdScreen() {
    delete m_background_texture;
    delete m_bird;
    for (Pipe* pipe : m_pipes) {
        delete pipe;
    }
    m_pipes.clear();
}

void FlappyBirdScreen::SetUpLevel() {
    m_background_texture = new Texture2D(m_renderer);
    m_background_texture->LoadFromFile("Images/FlappyBirdBackground.png");

    m_bird = new CharacterBird(m_renderer, "Images/FlappyBird.png", Vector2D(100, 250));

    m_pipe_spawn_timer = 0.0f;
    m_ground_level = 416.0f - 34; // Adjust ground level as needed
    m_pipe_spawn_distance = 300.0f; // Fixed distance between pipe pairs
    m_next_pipe_spawn_x = 512.0f; // Initial spawn position

    m_game_over = false;
}

void FlappyBirdScreen::Render() 
{
    m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
    m_bird->Render();
    for (Pipe* pipe : m_pipes) 
    {
        pipe->Render();
    }
    SDL_RenderCopy(m_renderer, m_scoreTexture, NULL, &m_scoreRect);

    if (m_game_over) 
    {
        RenderText("Game Over", { 255, 0, 0, 255 }, 180, 150);
        RenderText("Press R to replay", { 255, 255, 255, 255 }, 150, 200);
    }

}

void FlappyBirdScreen::Update(float deltaTime, SDL_Event e) 
{
    if (m_game_over) 
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) 
        {
            // Reset the game
            m_game_over = false;
            m_score = 0;
            delete m_bird;
            m_bird = new CharacterBird(m_renderer, "Images/FlappyBird.png", Vector2D(100, 250));
            for (Pipe* pipe : m_pipes) 
            {
                delete pipe;
            }
            m_pipes.clear();
            m_pipe_spawn_timer = 0.0f;
            m_next_pipe_spawn_x = 512.0f;

            UpdateScoreTexture();
        }
        return;
    }
    m_bird->Update(deltaTime, e);

    // Update the timer for spawning pipes
    m_pipe_spawn_timer += deltaTime;
    if (m_pipe_spawn_timer > 1.5f) 
    { // Adjust the spawn frequency 
        CreatePipe(m_next_pipe_spawn_x);
        m_pipe_spawn_timer = 0.0f;
    }

    for (auto pipe : m_pipes) 
    {
        pipe->Update(deltaTime, e);

        //Check score logic 
        if (!pipe->HasScored() && pipe->GetPosition().x < m_bird->GetPosition().x) 
        //checks if the pipe's x position is less than the bird's x position
        {
            m_score++;
            pipe->SetScored(true);
            UpdateScoreTexture();
        }
    }

    // Remove pipes that have gone off-screen
    m_pipes.erase(std::remove_if(m_pipes.begin(), m_pipes.end(), [](Pipe* pipe) 
        {
        bool offScreen = pipe->GetCollisionBox().x + pipe->GetCollisionBox().w < 0;
        if (offScreen) delete pipe;
        return offScreen;
        }), m_pipes.end());

    CheckCollisions();
}

void FlappyBirdScreen::UpdateScoreTexture()
{
    SDL_Color color = { 255, 255, 255, 255 }; 
    std::string scoreText = "Score: " + std::to_string(m_score);
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, scoreText.c_str(), color);

    SDL_DestroyTexture(m_scoreTexture); // Destroy old texture
    m_scoreTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    // Update the score rectangle size
    m_scoreRect.w = surface->w;
    m_scoreRect.h = surface->h;
}

void FlappyBirdScreen::RenderText(const std::string& message, SDL_Color color, int x, int y) 
{
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_FreeSurface(surface);

    SDL_RenderCopy(m_renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

void FlappyBirdScreen::CreatePipe(float xPosition) 
{
    int gap_y = rand() % 100 + 100; // Randomize pipe gap position within a more suitable range
    int gap_height = 100; // Height of the gap between the top and bottom pipes

    Pipe* topPipe = new Pipe(m_renderer, Vector2D(xPosition, gap_y - 200), true); // Top pipe
    Pipe* bottomPipe = new Pipe(m_renderer, Vector2D(xPosition, gap_y + gap_height), false); // Bottom pipe

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
            m_game_over = true; // Set the game over flag
            return; // Exit the method since the game is over
        }
    }

    if (birdBox.y + birdBox.h >= m_ground_level)
    {
        std::cout << "Bird hit the ground!" << std::endl;
        m_game_over = true; // Set the game over flag
    }
}
