#include "Game.h"

int main(int argc, char* argv[]) {
    if (!Game::getInstance().initialize("Pacman Remade", 800, 920)) {
        return 1;
    }

    Game::getInstance().run();

    return 0;
}