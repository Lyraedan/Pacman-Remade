#pragma once

#include <SDL_mixer.h>
#include <string>
#include <map>

class AudioManager {
public:
    static AudioManager& getInstance();
    void cleanup();

    bool loadSound(const std::string& fileName, const std::string& id);
    bool loadMusic(const std::string& fileName, const std::string& id);

    void playSound(const std::string& id);
    void playMusic(const std::string& id, int loops = -1);

private:
    AudioManager();
    ~AudioManager();
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, Mix_Chunk*> m_soundMap;
    std::map<std::string, Mix_Music*> m_musicMap;
};