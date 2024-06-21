#ifndef FLAPPYBIRDSCREEN_H
#define FLAPPYBIRDSCREEN_H

#include "GameScreen.h"
#include "GameScreenManager.h"
#include "CharacterBird.h"
#include "Pipe.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <vector>

class FlappyBirdScreen : public GameScreen
{
public:
    FlappyBirdScreen(SDL_Renderer* renderer, GameScreenManager* manager);
    ~FlappyBirdScreen();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;

private:
    void SetUpLevel();
    void CreatePipe(float xPosition);
    void CheckCollisions();
    void UpdateScoreTexture();
    void RenderText(const std::string& message, SDL_Color color, int x, int y);

    Texture2D* m_background_texture;
    CharacterBird* m_bird;
    TTF_Font* m_font;
    SDL_Texture* m_scoreTexture;
    SDL_Rect m_scoreRect;

    Texture2D* m_game_over_texture;
    Texture2D* m_replay_texture;

    std::vector<Pipe*> m_pipes;

    float m_pipe_spawn_timer;
    float m_ground_level;
    float m_pipe_spawn_distance; // Fixed distance between pipe pairs
    float m_next_pipe_spawn_x; // Next pipe spawn position
    int m_score;
    bool m_game_over;
};

#endif // FLAPPYBIRDSCREEN_H
