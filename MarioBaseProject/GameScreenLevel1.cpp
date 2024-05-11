#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) 
{
    SetLevelMap();
    SetUpLevel();
    //mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
    //luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330), m_level_map);
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
}

void GameScreenLevel1::Render() 
{
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
    mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
    luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330), m_level_map);
    return true;
}

void GameScreenLevel1::SetLevelMap()
{
    //clear any old naps
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
}