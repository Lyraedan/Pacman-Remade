#include "State_PacmanReady.h"
#include "State_PacmanActive.h" // The next state we'll transition to
#include <iostream>
#include "AudioManager.h"

void State_PacmanReady::enter(Entity* entity) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    std::cout << "Pacman entered ReadyState" << std::endl;
    
    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->playAnimation("idle");
    }

    pacman->setX(400);
    pacman->setY(320);

    AudioManager::getInstance().playSound("intro");
}

void State_PacmanReady::exit(Entity* entity) {
    std::cout << "Pacman exited ReadyState" << std::endl;
    m_timer = 0.0;
}

void State_PacmanReady::update(Entity* entity, double deltaTime) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    m_timer += deltaTime;

    // After 4 seconds, transition to the Active state
    if (m_timer >= 4.0) {
        //pacman->changeState(std::make_unique<State_PacmanActive>());
    }

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->update(deltaTime);
    }
}

void State_PacmanReady::render(Entity* entity, SDL_Renderer* renderer) {
    Pacman* pacman = static_cast<Pacman*>(entity);

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->render(renderer, pacman->getX(), pacman->getY(), pacman->getSize(), pacman->getSize(), 0.0);
    }
}