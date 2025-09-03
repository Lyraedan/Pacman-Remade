#pragma once

#include "State.h"
#include "Pacman.h"

class State_PacmanReady : public State {
public:
    void enter(Entity* entity) override;
    void exit(Entity* entity) override;
    void update(Entity* entity, double deltaTime) override;
    void render(Entity* entity, SDL_Renderer* renderer) override;
private:
    double m_timer = 0.0;
};