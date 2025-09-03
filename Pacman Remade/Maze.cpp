#include "Maze.h"
#include <fstream>
#include <iostream>

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