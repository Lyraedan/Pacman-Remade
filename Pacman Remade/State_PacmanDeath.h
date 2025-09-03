#pragma once

#include "State.h"
#include "Pacman.h"
#include <SDL.h>

class State_PacmanDeath : public State {
public:
    void enter(Entity* entity) override;
    void exit(Entity* entity) override;
    void update(Entity* entity, double deltaTime) override;
    void render(Entity* entity, SDL_Renderer* renderer) override;

private:
    double m_timer = 0.0;
    double m_animationLength = 2.0; // The total duration of the death animation
};