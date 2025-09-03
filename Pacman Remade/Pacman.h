#pragma once

#include "SpriteSheet.h"
#include "Entity.h"
#include "StateMachine.h"
#include "Maze.h" // Include the Maze header
#include <SDL.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Pacman : public Entity {
public:
    Pacman(int x, int y, int size, SDL_Texture* pacmanTexture, Maze* maze);
    ~Pacman();

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    int getSize() const { return m_size; }
    double getSpeed() const { return m_speed; }
    Direction getDirection() const { return m_direction; }
    SpriteSheet* getSpriteSheet() const { return m_spriteSheet; }
    Maze* getMaze() const { return m_maze; }
    int getTileX() const { return static_cast<int>(m_x / m_maze->getTileSize()); }
    int getTileY() const { return static_cast<int>(m_y / m_maze->getTileSize()); }

    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }
    void setDirection(Direction direction) { m_direction = direction; }
    void changeState(std::unique_ptr<State> newState);

    int getRenderX() const { return m_maze->getMazeOffsetX() + getTileX() * m_maze->getTileSize(); }
    int getRenderY() const { return m_maze->getMazeOffsetY() + getTileY() * m_maze->getTileSize(); }

    void moveToSpawn();

    int getLives() const { return lives; }
    void resetLives();
    void gainLife();
    void loseLife();

private:
    double m_x, m_y;
    double spawn_x, spawn_y;
    int m_size;
    Direction m_direction;
    double m_speed;

    int lives = 3;

    SpriteSheet* m_spriteSheet;
    Maze* m_maze;
    StateMachine m_stateMachine;

    void initializeAnimations();
};