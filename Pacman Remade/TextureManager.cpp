#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::cleanup() {
    for (auto const& texture : m_textureMap) {
        SDL_DestroyTexture(texture.second);
    }
    m_textureMap.clear();
}

bool TextureManager::loadTexture(const std::string& fileName, const std::string& id, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!newTexture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    m_textureMap[id] = newTexture;
    return true;
}

SDL_Texture* TextureManager::getTexture(const std::string& id) {
    if (m_textureMap.find(id) == m_textureMap.end()) {
        return nullptr;
    }
    return m_textureMap[id];
}