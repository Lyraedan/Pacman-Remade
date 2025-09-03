#pragma once

#include "Entity.h"
#include <SDL.h>

class Pellet : public Entity {
public:
    // Constructor takes position, size, and its texture
    Pellet(int x, int y, int size, SDL_Texture* texture, int tileX, int tileY);
    ~Pellet();

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);

    // Added methods for collecting and checking the pellet's state
    void collect();
    bool isCollected() const;

    void reset();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getTileX() const { return tile_x; }
    int getTileY() const { return tile_y; }
    
    int getSize() const { return m_size; }
    SDL_Texture* getTexture() const { return m_texture; }

private:
    int m_x, m_y;
    int tile_x, tile_y;
    int m_size;
    SDL_Texture* m_texture;

    bool m_isCollected;
};