#pragma once
#ifdef _GameScreenIntro_h
#define _GameScreenIntro_h
#endif // _GameScreenIntro_h

#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenIntro : public GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;
	GameScreenManager* m_manager;
	bool SetUpLevel();
};


