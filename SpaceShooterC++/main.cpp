#include "Game.h"
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;
    game.run();

    return 0;
}