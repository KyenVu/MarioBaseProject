#ifndef FLAPPY_BIRD_SCREEN_H
#define FLAPPY_BIRD_SCREEN_H

#include "GameScreen.h"
#include "GameScreenManager.h"
#include "CharacterBird.h"
#include "Pipe.h"
#include <vector>

class FlappyBirdScreen : public GameScreen {
public:
    FlappyBirdScreen(SDL_Renderer* renderer, GameScreenManager* manager);
    ~FlappyBirdScreen();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;

private:
    void SetUpLevel();
    void CreatePipe();
    void CheckCollisions();

    Texture2D* m_background_texture;
    CharacterBird* m_bird;
    std::vector<Pipe*> m_pipes;
    float m_pipe_spawn_timer;
    float m_ground_level;
};

#endif // FLAPPY_BIRD_SCREEN_H
