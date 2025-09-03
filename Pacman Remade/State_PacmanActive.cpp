#include "State_PacmanActive.h"
#include <iostream>
#include <SDL.h>

void State_PacmanActive::enter(Entity* entity) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    std::cout << "Pacman entered ActiveState" << std::endl;

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->playAnimation("active");
    }
}

void State_PacmanActive::exit(Entity* entity) {
    std::cout << "Pacman exited ActiveState" << std::endl;
}

void State_PacmanActive::update(Entity* entity, double deltaTime) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    Maze* maze = pacman->getMaze();

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        pacman->setDirection(UP);
    }
    else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        pacman->setDirection(DOWN);
    }
    else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        pacman->setDirection(LEFT);
    }
    else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        pacman->setDirection(RIGHT);
    }

    // Use double for accurate position calculations
    double nextX = static_cast<double>(pacman->getX());
    double nextY = static_cast<double>(pacman->getY());
    double speed = pacman->getSpeed() * deltaTime;

    switch (pacman->getDirection()) {
    case UP:
        nextY -= speed;
        break;
    case DOWN:
        nextY += speed;
        break;
    case LEFT:
        nextX -= speed;
        break;
    case RIGHT:
        nextX += speed;
        break;
    }

    // Check if the next tile is a wall
    int tileX = static_cast<int>((nextX + pacman->getSize() / 2) / maze->getTileSize());
    int tileY = static_cast<int>((nextY + pacman->getSize() / 2) / maze->getTileSize());

    if (maze->getGrid()[tileY][tileX] != 1) {
        // Update Pac-Man's position
        pacman->setX(static_cast<int>(nextX));
        pacman->setY(static_cast<int>(nextY));
    }

    // Update the animation
    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->update(deltaTime);
    }
}

void State_PacmanActive::render(Entity* entity, SDL_Renderer* renderer) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    if (pacman->getSpriteSheet()) {
        double angle = 0.0;
        switch (pacman->getDirection()) {
        case UP:
            angle = 270.0;
            break;
        case DOWN:
            angle = 90.0;
            break;
        case LEFT:
            angle = 180.0;
            break;
        case RIGHT:
            angle = 0.0;
            break;
        }
        pacman->getSpriteSheet()->render(renderer, pacman->getX(), pacman->getY(), pacman->getSize(), pacman->getSize(), angle);
    }
}