#include "StateMachine.h"

StateMachine::StateMachine() : m_currentState(nullptr) {}

StateMachine::~StateMachine() {}

void StateMachine::changeState(std::unique_ptr<State> newState, Entity* entity) {
    if (m_currentState) {
        m_currentState->exit(entity);
    }
    m_currentState = std::move(newState);
    if (m_currentState) {
        m_currentState->enter(entity);
    }
}

void StateMachine::update(Entity* entity, double deltaTime) {
    if (m_currentState) {
        m_currentState->update(entity, deltaTime);
    }
}

void StateMachine::render(Entity* entity, SDL_Renderer* renderer) {
    if (m_currentState) {
        m_currentState->render(entity, renderer);
    }
}