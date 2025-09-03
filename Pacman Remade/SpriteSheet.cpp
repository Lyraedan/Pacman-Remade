#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(SDL_Texture* texture)
    : m_texture(texture), m_currentAnimation(nullptr), m_currentFrameTime(0.0), m_currentFrameIndex(0) {
}

SpriteSheet::~SpriteSheet() {

}

void SpriteSheet::addAnimation(const std::string& name, const std::vector<SDL_Rect>& frames, double speed) {
    if (speed <= 0.0) {
        std::cerr << "Animation speed must be greater than 0." << std::endl;
        return;
    }
    m_animations[name] = { frames, speed };
}

void SpriteSheet::playAnimation(const std::string& name) {
    if (m_animations.count(name)) {
        m_currentAnimation = &m_animations[name];
        m_currentFrameIndex = 0;
        m_currentFrameTime = 0.0;
    }
    else {
        std::cerr << "Animation not found: " << name << std::endl;
        m_currentAnimation = nullptr;
    }
}

void SpriteSheet::update(double deltaTime) {
    if (!m_currentAnimation) return;

    m_currentFrameTime += deltaTime;
    double frameDuration = 1.0 / m_currentAnimation->speed;

    if (m_currentFrameTime >= frameDuration) {
        m_currentFrameIndex++;
        if (m_currentFrameIndex >= m_currentAnimation->frames.size()) {
            m_currentFrameIndex = 0; // Loop the animation
        }
        m_currentFrameTime -= frameDuration;
    }
}

void SpriteSheet::render(SDL_Renderer* renderer, int x, int y, int width, int height, double angle) {
    if (!m_currentAnimation || m_currentAnimation->frames.empty() || m_currentFrameIndex >= m_currentAnimation->frames.size()) {
        return;
    }

    const SDL_Rect& srcRect = m_currentAnimation->frames[m_currentFrameIndex];
    SDL_Rect destRect = { x, y, width, height };

    SDL_RenderCopyEx(renderer, m_texture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}