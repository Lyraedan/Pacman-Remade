#pragma once

#include <SDL.h>

class Window {
public:
    Window();
    ~Window();

    bool initialize(const char* title, int width, int height);
    void close();

    SDL_Window* getSDLWindow() const { return m_window; }
    SDL_Renderer* getSDLRenderer() const { return m_renderer; }

    bool isInitialized() const { return hasInit; }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool hasInit = false;
};