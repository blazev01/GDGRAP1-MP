#include <iostream>
#include <string>
#include <unordered_map>

#include "Controller/Game.hpp"

using namespace controllers;

int main(void) {
    Game MyGame = Game();

    MyGame.run();

    return 0;
}