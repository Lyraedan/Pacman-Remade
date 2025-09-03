#pragma once

#include "State.h"
#include <memory>

class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void changeState(std::unique_ptr<State> newState, Entity* entity);

    void update(Entity* entity, double deltaTime);
    void render(Entity* entity, SDL_Renderer* renderer);

private:
    std::unique_ptr<State> m_currentState;
};