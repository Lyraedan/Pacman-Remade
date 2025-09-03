#include "Pacman.h"
#include <iostream>
#include "Maze.h"

// Pacman now takes a Maze pointer in its constructor
Pacman::Pacman(int x, int y, int size, SDL_Texture* pacmanTexture, Maze* maze)
    : m_x(x), m_y(y), m_size(size), m_maze(maze), m_direction(RIGHT), m_speed(150.0) {

    m_spriteSheet = new SpriteSheet(pacmanTexture);
    initializeAnimations();

    if (m_spriteSheet) {
        m_spriteSheet->playAnimation("idle");
    }
}

Pacman::~Pacman() {

}

void Pacman::changeState(std::unique_ptr<State> newState) {
    m_stateMachine.changeState(std::move(newState), this);
}

void Pacman::initializeAnimations()
{
    m_spriteSheet->addAnimation("idle", {
        {0, 0, 32, 32}
        }, 1.0);

    int frameWidth = 32;
    int frameHeight = 32;

    std::vector<SDL_Rect> activeFrames;
    int activeFramesCount = 3;
    for (int i = 0; i < activeFramesCount; ++i) {
        activeFrames.push_back({ i * frameWidth, 0, frameWidth, frameHeight });
    }
    m_spriteSheet->addAnimation("active", activeFrames, 10.0);

    // Death animation loop
    std::vector<SDL_Rect> deathFrames;
    int deathFramesCount = 12;

    for (int i = 0; i < deathFramesCount; ++i) {
        deathFrames.push_back({ i * frameWidth, 96, frameWidth, frameHeight });
    }

    m_spriteSheet->addAnimation("death", deathFrames, 10.0);
}

void Pacman::update(double deltaTime) {
    m_stateMachine.update(this, deltaTime);
}

void Pacman::render(SDL_Renderer* renderer) {
    m_stateMachine.render(this, renderer);
}