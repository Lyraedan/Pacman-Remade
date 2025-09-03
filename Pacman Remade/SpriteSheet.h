#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include <map>

struct Animation {
    std::vector<SDL_Rect> frames;
    double speed; // Frames per second
};

class SpriteSheet {
public:
    SpriteSheet(SDL_Texture* texture);
    ~SpriteSheet();

    void addAnimation(const std::string& name, const std::vector<SDL_Rect>& frames, double speed);
    void playAnimation(const std::string& name);
    void update(double deltaTime);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height, double angle = 0.0);

private:
    SDL_Texture* m_texture;
    std::map<std::string, Animation> m_animations;
    Animation* m_currentAnimation;
    double m_currentFrameTime;
    int m_currentFrameIndex;
};