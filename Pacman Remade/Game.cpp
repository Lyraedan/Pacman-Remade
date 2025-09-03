#include "Game.h"
#include "TextureManager.h"
#include "State_PacmanReady.h"
#include "State_PacmanActive.h"
#include "State_PacmanDeath.h"
#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

Game::Game() : m_isRunning(false), m_mazeTexture(nullptr) {
    // Constructor initializes members
}

Game::~Game() {
    // Destructor
}

bool Game::initialize(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        return false;
    }

    m_window = std::make_unique<Window>();
    m_window->initialize(title, width, height);
    if (!m_window->isInitialized()) {
        return false;
    }

    if (!loadTextures()) {
        std::cerr << "Failed to load game textures. Exiting." << std::endl;
        return false;
    }

    m_mazeTexture = TextureManager::getInstance().getTexture("playfield");

    int tileSize = 32;
    m_maze = std::make_unique<Maze>(tileSize);
    if (!m_maze->loadFromTextFile("res/map.txt")) {
        std::cerr << "Failed to load maze from file!" << std::endl;
        return false;
    }

    SDL_Texture* pelletTexture = TextureManager::getInstance().getTexture("pellet");
    int pelletSize = 32;

    int offsetX = 180;
    int offsetY = 68;
    // Iterate through the maze grid to create pellets
    for (int y = 0; y < m_maze->getHeight(); ++y) {
        for (int x = 0; x < m_maze->getWidth(); ++x) {
            if (m_maze->getGrid()[y][x] == 0) {
                // Calculate the position for the pellet
                int pelletX = offsetX + (x * tileSize) / 2;
                int pelletY = offsetY + (y * tileSize) / 2;

                // Create a new pellet and add it to the vector
                m_pellets.push_back(std::make_unique<Pellet>(pelletX, pelletY, pelletSize, pelletTexture));
            }
            else if (m_maze->getGrid()[y][x] == 6) {
                int pacmanSize = 32;
                int spawnX = offsetX + (x * tileSize) / 2;
                int spawnY = offsetY + (y * tileSize) / 2;
                m_pacman = std::make_unique<Pacman>(
                    spawnX,
                    spawnY,
                    pacmanSize,
                    TextureManager::getInstance().getTexture("pacman"),
                    m_maze.get()
                );
            }
        }
    }

    // Set Pac-Man to his initial state
    m_pacman->changeState(std::make_unique<State_PacmanReady>());

    m_isRunning = true;
    return true;
}

void Game::run() {
    Uint64 lastTime = SDL_GetTicks64();
    double deltaTime = 0.0;

    while (m_isRunning) {
        Uint64 currentTime = SDL_GetTicks64();
        deltaTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_isRunning = false;
            }
        }

        update(deltaTime);
        render(m_window->getSDLRenderer());
    }
}

void Game::update(float deltaTime)
{
    m_pacman->update(deltaTime);
}

void Game::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (m_mazeTexture) {
        SDL_RenderCopy(renderer, m_mazeTexture, NULL, NULL);
    }

    for (const auto& pellet : m_pellets) {
        pellet->render(renderer);
    }

    m_pacman->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    TextureManager::getInstance().cleanup();
    IMG_Quit();
    SDL_Quit();
}

bool Game::isRunning() const {
    return m_isRunning;
}

bool Game::loadTextures() {
    if (!TextureManager::getInstance().loadTexture("res/gfx/playfield.png", "playfield", m_window->getSDLRenderer())) {
        std::cerr << "Failed to load maze texture!" << std::endl;
        return false;
    }

    if (!TextureManager::getInstance().loadTexture("res/gfx/pacman.png", "pacman", m_window->getSDLRenderer())) {
        std::cerr << "Failed to load Pac-Man spritesheet!" << std::endl;
        return false;
    }

    if (!TextureManager::getInstance().loadTexture("res/gfx/pellet.png", "pellet", m_window->getSDLRenderer())) {
        std::cerr << "Failed to load Pallet texture!" << std::endl;
        return false;
    }

    return true;
}