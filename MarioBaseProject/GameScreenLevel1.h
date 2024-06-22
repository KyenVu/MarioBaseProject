#pragma once
#ifdef GameScreenLevel1_h
#define GameScreenLevel1_h
#endif // GameScreenLevel1_h

#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "PowBlock.h"

using namespace std;

class PowBlock;
class Character;
class GameScreenLevel1 : public GameScreen
{
public:
    GameScreenLevel1(SDL_Renderer* renderer);
    ~GameScreenLevel1();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    void UpdatePowBlock();
    void DoScreenShake();

private:
    vector<CharacterKoopa*> m_enemies;
    vector<CharacterCoin*> m_coins;

    Texture2D* m_background_texture;
    CharacterMario* mario;
    CharacterLuigi* luigi;
    CharacterKoopa* koopa;
    LevelMap* m_level_map;
    PowBlock* m_pow_block;
    TTF_Font* m_font;

    bool m_screenshake;
    bool m_game_over;

    float m_shake_time;
    float m_wobble;
    float m_background_yPos;
    float m_koopa_spawn_timer = 15.0f;
    int m_score = 0;
    int dead = 0;

    bool SetUpLevel();
    void SetLevelMap();
    void UpdateEnemies(float deltaTime, SDL_Event e);
    void UpdateKoopaSpawn(float deltaTime);
    void CreateKoopa(Vector2D position, FACING direction, float speed);
    void CreateCoin(Vector2D position);
    void UpdateCoins(float deltaTime, SDL_Event e);
    void RenderScore();
};
