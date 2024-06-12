#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) 
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
}

// Render to Game screen level 1
void GameScreenLevel1::Render() 
{
    //draw enemies
    for (int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies[i]->Render();
    }

    for (int i = 0; i < m_coins.size(); i++) 
    {
        m_coins[i]->Render();
    }

    // draw background
    m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

    mario->Render();
    luigi->Render();
    m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
    //update character
    mario->Update(deltaTime, e);
    luigi->Update(deltaTime, e);

    UpdatePowBlock();
    UpdateEnemies(deltaTime, e);
    UpdateKoopaSpawn(deltaTime);

    UpdateCoins(deltaTime, e);

    //do shake screen
    if (m_screenshake)
    {
        m_shake_time -= deltaTime;
        m_wobble++;
        m_background_yPos = sin(m_wobble);
        m_background_yPos *= 3.0f;
        // end shake screen
        if (m_shake_time <= 0.0f)
        {
            m_shake_time = false;
            m_background_yPos = 0.0f;
        }
    }

    if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
    {
        cout << "Box hit!" << endl;
    }
    //if (Collisions::Instance()->Circle(mario, luigi))
    //{
    //    cout << "Circle hit" << endl;
    //}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
    koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
    m_enemies.push_back(koopa);
}


bool GameScreenLevel1::SetUpLevel() 
{
    //create background texture
    m_background_texture = new Texture2D(m_renderer);
    m_pow_block = new PowBlock(m_renderer, m_level_map);
    m_screenshake = false;
    m_background_yPos = 0.0f;



    if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) 
    {
        cout << "Failed to load background texture!" << endl;
        return false;
    }
  

    mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 300), m_level_map);
    luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 300), m_level_map);

    CreateKoopa(Vector2D(150, 330), FACING_LEFT, KOOPA_SPEED);
    CreateKoopa(Vector2D(325, 30), FACING_RIGHT, KOOPA_SPEED);

    CreateCoin(Vector2D(200, 300));
    CreateCoin(Vector2D(300, 300));

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
                // Collect the coin, add points, etc.
                delete m_coins[i];
                m_coins.erase(m_coins.begin() + i);
                // Add points or handle collection logic here
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
                // Ignore collisions if behind pipe
            }
            else 
            {
                if (Collisions::Instance()->Circle(m_enemies[i], mario)) 
                {
                    if (m_enemies[i]->GetInjured()) 
                    {
                        m_enemies[i]->SetAlive(false);
                    }
                    else {

                        // Kill Mario
                    }
                } if (Collisions::Instance()->Circle(m_enemies[i], luigi)) 
                {
                    if (m_enemies[i]->GetInjured()) 
                    {
                        m_enemies[i]->SetAlive(false);
                    }
                    else {

                        // Kill Luigi
                    }
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