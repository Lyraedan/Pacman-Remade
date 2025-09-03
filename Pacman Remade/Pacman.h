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

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getSize() const { return m_size; }
    double getSpeed() const { return m_speed; }
    Direction getDirection() const { return m_direction; }
    SpriteSheet* getSpriteSheet() const { return m_spriteSheet; }
    Maze* getMaze() const { return m_maze; }

    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
    void setDirection(Direction direction) { m_direction = direction; }
    void changeState(std::unique_ptr<State> newState);

private:
    int m_x, m_y;
    int m_size;
    Direction m_direction;
    double m_speed;

    SpriteSheet* m_spriteSheet;
    Maze* m_maze;
    StateMachine m_stateMachine;

    void initializeAnimations();
};