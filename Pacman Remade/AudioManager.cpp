#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() {
    
}

AudioManager::~AudioManager() {
    
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::cleanup() {
    for (auto const& sound : m_soundMap) {
        Mix_FreeChunk(sound.second);
    }
    m_soundMap.clear();

    for (auto const& music : m_musicMap) {
        Mix_FreeMusic(music.second);
    }
    m_musicMap.clear();
}

bool AudioManager::loadSound(const std::string& fileName, const std::string& id) {
    Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
        return false;
    }
    m_soundMap[id] = sound;
    return true;
}

bool AudioManager::loadMusic(const std::string& fileName, const std::string& id) {
    Mix_Music* music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    m_musicMap[id] = music;
    return true;
}

void AudioManager::playSound(const std::string& id) {
    if (m_soundMap.find(id) != m_soundMap.end()) {
        Mix_PlayChannel(-1, m_soundMap[id], 0);
    }
    else {
        std::cerr << "Sound ID not found: " << id << std::endl;
    }
}

void AudioManager::playMusic(const std::string& id, int loops) {
    if (m_musicMap.find(id) != m_musicMap.end()) {
        Mix_PlayMusic(m_musicMap[id], loops);
    }
    else {
        std::cerr << "Music ID not found: " << id << std::endl;
    }
}