#pragma once
#ifdef GameScreenLevel1.h
#define GameScreenLevel1.h
#endif // GameScreenLevel1.h

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"

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
	Texture2D* m_background_texture;
	CharacterMario* mario;
	CharacterLuigi* luigi;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;


	bool SetUpLevel();

	void SetLevelMap();

};
