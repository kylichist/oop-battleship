#include <iostream>
#include <string>

#include "../include/ConsoleInputHandler.hpp"

Action ConsoleInputHandler::getAction() {
    std::string source;
    while (true) {
        std::getline(std::cin, source);
        if (source == "select") {
            return Action::SELECT;
        } else if (source == "attack") {
            return Action::ATTACK;
        } else if (source == "use ability") {
            return Action::USE_ABILITY;
        } else {
            continue;
        }
    }
}

Coordinates ConsoleInputHandler::getCoordinates() {
    size_t x, y;
    std::cin >> x >> y;
    return Coordinates(x, y);
}

bool ConsoleInputHandler::getChoice() {
    std::string source;
    std::getline(std::cin, source);
    if (source == "" || source == "y" || source == "yes") {
        return true;
    }
    return false;
}
