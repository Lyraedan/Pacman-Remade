#pragma once

#include "Entity.h"
#include <SDL.h>

class State {
public:
    virtual ~State() {}

    virtual void enter(Entity* entity) = 0;
    virtual void exit(Entity* entity) = 0;
    virtual void update(Entity* entity, double deltaTime) = 0;
    virtual void render(Entity* entity, SDL_Renderer* renderer) = 0;
};