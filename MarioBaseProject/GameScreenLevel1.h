#pragma once
#ifdef GameScreenLevel1.h
#define GameScreenLevel1.h
#endif // GameScreenLevel1.h

#include <iostream>
#include <vector>
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
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

	Texture2D* m_background_texture;
	CharacterMario* mario;
	CharacterLuigi* luigi;
	CharacterKoopa* koopa;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	bool m_screenshake;

	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_koopa_spawn_timer = 15.0f;


	bool SetUpLevel();

	void SetLevelMap();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateKoopaSpawn(float deltaTime);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

};
