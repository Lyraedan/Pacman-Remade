#include "Maze.h"
#include <fstream>
#include <iostream>
#include "TextureManager.h"

Maze::Maze(int tileSize) : m_tileSize(tileSize), m_width(0), m_height(0) {}

bool Maze::loadFromTextFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open maze file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        for (char c : line) {
            switch (c) {
            case 'x': // Wall
                row.push_back(1);
                break;
            case '.': // Pellet
            case 'o': // Big pellet
                row.push_back(0);
                break;
            case ' ': // Unblocked moveable space
                row.push_back(-1);
                break;
            case 'T':
                row.push_back(2);
                break;
            case 'G': // Ghost spawn
                row.push_back(3);
                break;
            case 'R': // Ghost return point
                row.push_back(5);
                break;
            case 'S': // Pac-Man spawn / fruit spawn
                row.push_back(6);
                break;
            default:
                row.push_back(-1); // Default to a path for any unknown character
                break;
            }
        }
        m_grid.push_back(row);
    }

    if (!m_grid.empty()) {
        m_height = m_grid.size();
        m_width = m_grid[0].size();
    }

    file.close();
    return true;
}

const std::vector<std::vector<int>>& Maze::getGrid() const {
    return m_grid;
}

int Maze::getTileSize() const {
    return m_tileSize;
}

int Maze::getWidth() const {
    return m_width;
}

int Maze::getHeight() const {
    return m_height;
}

int Maze::getTileAt(int x, int y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        return m_grid[y][x];
    }
    return -2;
}

void Maze::render_maze(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    int offsetX = 90;
    int offsetY = 120;

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            // Only draw lines if the current tile is a wall
            if (m_grid[y][x] == 1) {
                // Top line
                if (y == 0 || m_grid[y - 1][x] != 1) {
                    SDL_RenderDrawLine(renderer,
                        offsetX + x * m_tileSize,
                        offsetY + y * m_tileSize,
                        offsetX + (x + 1) * m_tileSize,
                        offsetY + y * m_tileSize
                    );
                }

                // Bottom line
                if (y == m_height - 1 || m_grid[y + 1][x] != 1) {
                    SDL_RenderDrawLine(renderer,
                        offsetX + x * m_tileSize,
                        offsetY + (y + 1) * m_tileSize,
                        offsetX + (x + 1) * m_tileSize,
                        offsetY + (y + 1) * m_tileSize
                    );
                }

                // Left line
                if (x == 0 || m_grid[y][x - 1] != 1) {
                    SDL_RenderDrawLine(renderer,
                        offsetX + x * m_tileSize,
                        offsetY + y * m_tileSize,
                        offsetX + x * m_tileSize,
                        offsetY + (y + 1) * m_tileSize
                    );
                }

                // Right line
                if (x == m_width - 1 || m_grid[y][x + 1] != 1) {
                    SDL_RenderDrawLine(renderer,
                        offsetX + (x + 1) * m_tileSize,
                        offsetY + y * m_tileSize,
                        offsetX + (x + 1) * m_tileSize,
                        offsetY + (y + 1) * m_tileSize
                    );
                }
            }
        }
    }

    // Top border
    SDL_RenderDrawLine(renderer,
        offsetX,
        offsetY,
        offsetX + m_width * m_tileSize,
        offsetY
    );

    // Bottom border
    SDL_RenderDrawLine(renderer,
        offsetX,
        offsetY + m_height * m_tileSize,
        offsetX + m_width * m_tileSize,
        offsetY + m_height * m_tileSize
    );

    // Left border
    SDL_RenderDrawLine(renderer,
        offsetX,
        offsetY,
        offsetX,
        offsetY + m_height * m_tileSize
    );

    // Right border
    SDL_RenderDrawLine(renderer,
        offsetX + m_width * m_tileSize,
        offsetY,
        offsetX + m_width * m_tileSize,
        offsetY + m_height * m_tileSize
    );
}
void Maze::debug_render(SDL_Renderer* renderer)
{
    SDL_Texture* wallTexture = TextureManager::getInstance().getTexture("debug_wall");

    int offsetX = 90;
    int offsetY = 120;

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            // If the tile is a wall (value 1)
            if (m_grid[y][x] == 1) {
                SDL_Rect destRect = { offsetX + (x * m_tileSize), offsetY + (y * m_tileSize), m_tileSize, m_tileSize };
                SDL_RenderCopy(renderer, wallTexture, NULL, &destRect);
            }
        }
    }
}
