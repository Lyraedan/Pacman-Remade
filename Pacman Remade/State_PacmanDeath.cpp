#include "State_PacmanDeath.h"
#include "State_PacmanReady.h" // Transition back to the Ready state
#include <iostream>
#include "AudioManager.h"

void State_PacmanDeath::enter(Entity* entity) {
    Pacman* pacman = static_cast<Pacman*>(entity);
    std::cout << "Pacman entered DeathState" << std::endl;

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->playAnimation("death");
    }

    AudioManager::getInstance().playSound("pacman_death");
}

void State_PacmanDeath::exit(Entity* entity) {
    std::cout << "Pacman exited DeathState" << std::endl;
    m_timer = 0.0;
}

void State_PacmanDeath::update(Entity* entity, double deltaTime) {
    Pacman* pacman = static_cast<Pacman*>(entity);

    pacman->setDirection(RIGHT);

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->update(deltaTime);
    }

    m_timer += deltaTime;

    if (m_timer >= m_animationLength) {
        pacman->changeState(std::make_unique<State_PacmanReady>());
    }
}

void State_PacmanDeath::render(Entity* entity, SDL_Renderer* renderer) {
    Pacman* pacman = static_cast<Pacman*>(entity);

    if (pacman->getSpriteSheet()) {
        pacman->getSpriteSheet()->render(renderer, pacman->getX(), pacman->getY(), pacman->getSize(), pacman->getSize(), 0.0);
    }
}