#include "Pellet.h"
#include "AudioManager.h"

Pellet::Pellet(int x, int y, int size, SDL_Texture* texture, int tileX, int tileY)
    : m_x(x), m_y(y), m_size(size), m_texture(texture), m_isCollected(false), tile_x(tileX), tile_y(tileY) {
}

Pellet::~Pellet() {
    
}

void Pellet::update(double deltaTime) {
    
}

void Pellet::render(SDL_Renderer* renderer) {
    if (m_texture && !m_isCollected) {
        SDL_Rect destRect = { m_x, m_y, m_size, m_size };
        SDL_RenderCopy(renderer, m_texture, NULL, &destRect);
    }
}

void Pellet::collect() {
    m_isCollected = true;
    AudioManager::getInstance().playSound("pacman_waka");
}

bool Pellet::isCollected() const {
    return m_isCollected;
}

void Pellet::reset()
{
    m_isCollected = false;
}
