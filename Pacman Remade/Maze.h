#pragma once

#include <vector>
#include <string>
#include <SDL.h>

class Maze {
public:
    Maze(int tileSize);
    bool loadFromTextFile(const std::string& filePath);
    const std::vector<std::vector<int>>& getGrid() const;
    int getTileSize() const;
    int getWidth() const;
    int getHeight() const;
    int getTileAt(int x, int y) const;

    int getMazeOffsetX() const { return 90; }
    int getMazeOffsetY() const { return 120; }
    void render_maze(SDL_Renderer* renderer);
    void debug_render(SDL_Renderer* renderer);

private:
    std::vector<std::vector<int>> m_grid;
    int m_tileSize;
    int m_width;
    int m_height;
};