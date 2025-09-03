#pragma once

#include <SDL.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager& getInstance();
    void cleanup();

    bool loadTexture(const std::string& fileName, const std::string& id, SDL_Renderer* renderer);
    SDL_Texture* getTexture(const std::string& id);

private:
    TextureManager() {}
    ~TextureManager() {}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::map<std::string, SDL_Texture*> m_textureMap;
};