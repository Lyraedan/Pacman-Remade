#pragma once

#include "State.h"
#include "Pacman.h"
#include <SDL.h>

class State_PacmanActive : public State {
public:
    void enter(Entity* entity) override;
    void exit(Entity* entity) override;
    void update(Entity* entity, double deltaTime) override;
    void render(Entity* entity, SDL_Renderer* renderer) override;
};