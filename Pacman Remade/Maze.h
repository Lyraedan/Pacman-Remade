#pragma once

#include <vector>
#include <string>

class Maze {
public:
    Maze(int tileSize);
    bool loadFromTextFile(const std::string& filePath);
    const std::vector<std::vector<int>>& getGrid() const;
    int getTileSize() const;
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::vector<int>> m_grid;
    int m_tileSize;
    int m_width;
    int m_height;
};