#include "Game.h"

int main(int argc, char* argv[]) {
    Game myGame;

    if (!myGame.initialize("Pacman Remade", 800, 920)) {
        return 1;
    }

    myGame.run();

    return 0;
}