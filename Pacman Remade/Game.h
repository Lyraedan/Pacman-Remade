#pragma once

#include "Window.h"
#include "Pacman.h"
#include "Maze.h"
#include "TextureManager.h"
#include <memory>
#include <SDL.h>
#include "Pellet.h"

class Game {
public:
    Game();
    ~Game();

    bool initialize(const char* title, int width, int height);
    void run();
    void update(double deltaTime);
    void render(SDL_Renderer* renderer);
    void cleanup();
    bool isRunning() const;

private:
    bool m_isRunning;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Pacman> m_pacman;
    std::unique_ptr<Maze> m_maze;
    std::vector<std::unique_ptr<Pellet>> m_pellets;
    SDL_Texture* m_mazeTexture;

    bool loadTextures();
    bool loadAudio();
};