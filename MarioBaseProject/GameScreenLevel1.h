#pragma once
#ifdef GameScreenLevel1.h
#define GameScreenLevel1.h
#endif // GameScreenLevel1.h

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

class GameScreenLevel1 : public GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();

};
