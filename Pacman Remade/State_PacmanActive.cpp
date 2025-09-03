#include "State_PacmanActive.h"
#include <iostream>
#include <SDL.h>
#include "State_PacmanDeath.h"
#include "Game.h"

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
    else if (state[SDL_SCANCODE_SPACE]) {
        pacman->changeState(std::make_unique<State_PacmanDeath>());
    }

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

    int tileX = static_cast<int>(nextX / maze->getTileSize());
    int tileY = static_cast<int>(nextY / maze->getTileSize());

    int nextTileValue = maze->getTileAt(tileX, tileY);
    if (nextTileValue != 1 && nextTileValue != -2) {
        pacman->setX(nextX);
        pacman->setY(nextY);
        // Is pellet
        if (nextTileValue == 0) {
            Game::getInstance().collectPelletAt(tileX, tileY);
        }
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

        pacman->getSpriteSheet()->render(renderer, pacman->getRenderX(), pacman->getRenderY(), pacman->getSize(), pacman->getSize(), angle);
    }
}