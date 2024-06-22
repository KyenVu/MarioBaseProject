#include "GameScreenLevel1.h"
#include <SDL_ttf.h>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer), m_score(0) // Initialize score
{
    SetLevelMap();
    SetUpLevel();
    
}

GameScreenLevel1::~GameScreenLevel1()
{
    delete m_background_texture;
    m_background_texture = nullptr;

    delete mario;
    mario = nullptr;

    delete luigi;
    luigi = nullptr;

    delete m_pow_block;
    m_pow_block = nullptr;

    m_level_map = nullptr;

    for (int i = 0; i < m_enemies.size(); i++)
    {
        delete m_enemies[i];
    }
    m_enemies.clear();

    for (int i = 0; i < m_coins.size(); i++)
    {
        delete m_coins[i];
    }
    m_coins.clear();

    // Clean up font
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

// Render to Game screen level 1
void GameScreenLevel1::Render()
{
    // Draw background
    m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

    // Draw enemies
    for (int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies[i]->Render();
    }

    // Draw coins
    for (int i = 0; i < m_coins.size(); i++)
    {
        m_coins[i]->Render();
    }

    // Render Mario and Luigi if they are alive
    if (mario->GetAlive())
    {
        mario->Render();
    }
    if (luigi->GetAlive())
    {
        luigi->Render();
    }

    // Render POW block
    m_pow_block->Render();

    // Render score
    RenderScore();

    if (m_game_over)
    {
        SDL_Color color = { 255, 0, 0, 255 };
        std::string gameOverText = "You Lose! Press 1 to reset.";
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, gameOverText.c_str(), color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

        int text_width = surfaceMessage->w;
        int text_height = surfaceMessage->h;
        SDL_Rect message_rect = { SCREEN_WIDTH / 2 - text_width / 2, SCREEN_HEIGHT / 2 - text_height / 2, text_width, text_height };

        SDL_RenderCopy(m_renderer, message, NULL, &message_rect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
    }
    else if (m_score >= 10)
    {
        SDL_Color color = { 255, 0, 0, 255 };
        std::string winText = "You Win! Press 2 to continue.";
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, winText.c_str(), color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

        int text_width = surfaceMessage->w;
        int text_height = surfaceMessage->h;
        SDL_Rect message_rect = { SCREEN_WIDTH / 2 - text_width / 2, SCREEN_HEIGHT / 2 - text_height / 2, text_width, text_height };

        SDL_RenderCopy(m_renderer, message, NULL, &message_rect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
    }
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
    if (m_game_over)
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1)
        {
            // Reset the game
            SetUpLevel();
            m_score = 0;
            m_game_over = false;
            mario->SetAlive(true);
            luigi->SetAlive(true);
        }
        return;
    }

    // Update characters if they are alive
    if (mario->GetAlive())
    {
        mario->Update(deltaTime, e);
    }
    if (luigi->GetAlive())
    {
        luigi->Update(deltaTime, e);
    }

    UpdatePowBlock();
    UpdateEnemies(deltaTime, e);
    UpdateKoopaSpawn(deltaTime);

    UpdateCoins(deltaTime, e);

    // Do shake screen
    if (m_screenshake)
    {
        m_shake_time -= deltaTime;
        m_wobble++;
        m_background_yPos = sin(m_wobble);
        m_background_yPos *= 3.0f;
        // End shake screen
        if (m_shake_time <= 0.0f)
        {
            m_screenshake = false;
            m_background_yPos = 0.0f;
        }
    }

    if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
    {
        cout << "Box hit!" << endl;
    }
    // Check if both characters are dead to set game over state
    if (!mario->GetAlive() && !luigi->GetAlive())
    {
        m_game_over = true;
    }
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
    koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
    m_enemies.push_back(koopa);
}


bool GameScreenLevel1::SetUpLevel()
{
    // Create background texture
    m_background_texture = new Texture2D(m_renderer);
    m_pow_block = new PowBlock(m_renderer, m_level_map);
    m_screenshake = false;
    m_background_yPos = 0.0f;

    if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
    {
        cout << "Failed to load background texture!" << endl;
        return false;
    }

    // Load font
    m_font = TTF_OpenFont("PIXEARG_.ttf", 28);
    if (!m_font)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 300), m_level_map);
    luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 300), m_level_map);

    mario->SetAlive(true); 
    luigi->SetAlive(true); 

    CreateKoopa(Vector2D(150, 30), FACING_LEFT, KOOPA_SPEED);
    CreateKoopa(Vector2D(325, 30), FACING_RIGHT, KOOPA_SPEED);

    CreateCoin(Vector2D(300, 30));
    CreateCoin(Vector2D(200, 30));
    CreateCoin(Vector2D(100, 30));
    CreateCoin(Vector2D(400, 30));
    CreateCoin(Vector2D(200, 100));
    CreateCoin(Vector2D(300, 100));

    return true;
}

void GameScreenLevel1::SetLevelMap()
{
    //clear any old maps
    if (m_level_map != nullptr)
    {
        delete m_level_map;
    }

    int map[MAP_HEIGHT][MAP_WIDTH] =
    {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    //set the new one 
    m_level_map = new LevelMap(map);

}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
    CharacterCoin* coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
    m_coins.push_back(coin);
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
    if (!m_coins.empty())
    {
        for (unsigned int i = 0; i < m_coins.size(); i++)
        {
            m_coins[i]->Update(deltaTime, e);
            // Check for collision with players and remove coin if collected
            if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_coins[i]->GetCollisionBox()) ||
                Collisions::Instance()->Box(luigi->GetCollisionBox(), m_coins[i]->GetCollisionBox()))
            {
                // Collect the coin, add points.
                delete m_coins[i];
                m_coins.erase(m_coins.begin() + i);
                m_score += 1;
                cout << "Coin collected! Score: " << m_score << endl;

            }
        }
    }
}



void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
    if (!m_enemies.empty())
    {
        int enemyIndexToDelete = -1;
        for (unsigned int i = 0; i < m_enemies.size(); i++)
        {
            // Check if the enemy is on the bottom row of tiles
            if (m_enemies[i]->GetPosition().y > 300.0f)
            {
                // Is the enemy off-screen to the left/right?
                if (m_enemies[i]->GetPosition().x < (-m_enemies[i]->GetCollisionBox().width * 0.5f) ||
                    m_enemies[i]->GetPosition().x > SCREEN_WIDTH)
                {
                    m_enemies[i]->SetAlive(false);
                }
            }
            else
            {
                m_enemies[i]->CheckForBounderies();
            }

            // Now do the update
            m_enemies[i]->Update(deltaTime, e);
            // Check to see if enemy collides with player
            if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) &&
                (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
            {
               
            }
            else
            {
                if (Collisions::Instance()->Circle(m_enemies[i], mario))
                {
                    if (m_enemies[i]->GetInjured())
                    {
                        m_enemies[i]->SetAlive(false);
                        m_score += 1;
                    }
                    else
                    {
                        // Kill Mario
                        cout << "Mario killed by Koopa!" << endl;
                        mario->SetAlive(false);
                    }
                }
                if (Collisions::Instance()->Circle(m_enemies[i], luigi))
                {
                    if (m_enemies[i]->GetInjured())
                    {
                        m_enemies[i]->SetAlive(false);
                        m_score += 1;
                    }
                    else
                    {
                        // Kill Luigi
                        cout << "Luigi killed by Koopa!" << endl;
                        luigi->SetAlive(false);
                    }
                }
                // Check if Mario or Luigi jumps on the Koopa's head
                if (Collisions::Instance()->Box(mario->GetFeetCollisionBox(), m_enemies[i]->GetHeadCollisionBox()))
                {
                    m_enemies[i]->SetAlive(false);
                    m_score += 1;
                    mario->Bounce();
                }
                if (Collisions::Instance()->Box(luigi->GetFeetCollisionBox(), m_enemies[i]->GetHeadCollisionBox()))
                {
                    m_enemies[i]->SetAlive(false);
                    m_score += 1;
                    luigi->Bounce();
                }
            }
            // If the enemy is no longer alive then schedule it for deletion
            if (!m_enemies[i]->GetAlive())
            {
                enemyIndexToDelete = i;
            }
        }
        // Remove dead enemies - 1 each update
        if (enemyIndexToDelete != -1)
        {
            m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
        }
    }

}

void GameScreenLevel1::UpdateKoopaSpawn(float deltaTime)
{
    m_koopa_spawn_timer -= deltaTime;
    if (m_koopa_spawn_timer <= 0.0f)
    {
        CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
        cout << "koopa spawned" << endl;
        // Reset the timer
        m_koopa_spawn_timer = 15.0f;
    }
}


void GameScreenLevel1::UpdatePowBlock()
{
    if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
    {
        cout << "Box hit!" << endl;
        //Collide while jumping
        if (mario->IsJumping())
        {
            DoScreenShake();
            m_pow_block->TakeHit();
            mario->CancleJump();
        }
    }if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
    {
        cout << "Box hit!" << endl;
        //Collide while jumping
        if (luigi->IsJumping())
        {
            DoScreenShake();
            m_pow_block->TakeHit();
            luigi->CancleJump();
        }
    }

}

void GameScreenLevel1::DoScreenShake()
{
    m_screenshake = true;
    m_shake_time = SHAKE_DURATION;
    m_wobble = 0.0f;

    // Loop through the enemies vector and call TakeDamage() on each Koopa
    for (unsigned int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies[i]->TakeDamage();
    }
}

void GameScreenLevel1::RenderScore()
{
    SDL_Color color = { 255, 255, 255, 255 }; // White color
    std::string scoreText = "Score: " + std::to_string(m_score);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, scoreText.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int text_width = surfaceMessage->w;
    int text_height = surfaceMessage->h;
    SDL_Rect message_rect = { 10, 10, text_width, text_height }; // Adjust the position and size as needed

    SDL_RenderCopy(m_renderer, message, NULL, &message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}
