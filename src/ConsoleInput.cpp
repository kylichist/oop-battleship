#include <iostream>
#include <limits>
#include <sstream>

#include "../include/ConsoleInput.hpp"

ConsoleInput::ConsoleInput() {
    config = {{'w', GameCommand::MOVE_UP},   {'a', GameCommand::MOVE_LEFT},
              {'s', GameCommand::MOVE_DOWN}, {'d', GameCommand::MOVE_RIGHT},
              {'z', GameCommand::ATTACK},    {'x', GameCommand::USE_ABILITY},
              {'l', GameCommand::LOAD},      {'p', GameCommand::SAVE},
              {'h', GameCommand::HELP},      {'q', GameCommand::QUIT}};
}

GameCommand ConsoleInput::requestCommand(std::string msg) {
    if (msg != "") {
        std::cout << msg << std::endl;
    }
    std::string line;
    while (true) {
        if (std::cin.eof()) {
            return GameCommand::QUIT;
        }
        std::getline(std::cin, line);
        if (line.size() > 1 || config.count(line[0]) == 0) {
            std::cout << "Unknown command." << std::endl;
        } else {
            return config[line[0]];
        }
    }
}

bool ConsoleInput::requestChoice(std::string msg) {
    std::cout << msg << " (y/n):" << std::endl;
    std::string source;
    std::getline(std::cin, source);
    if (source == "" || source == "y" || source == "yes") {
        return true;
    }
    return false;
}

std::string ConsoleInput::requestString(std::string msg) {
    if (msg != "") {
        std::cout << msg << std::endl;
    }
    std::string source;
    std::getline(std::cin, source);
    return source;
}

void ConsoleInput::loadConfiguration(ControlConfiguration config) {
    this->config = config;
}

std::string ConsoleInput::getInfo() {
    std::stringstream ss;
    for (auto it = config.begin(); it != config.end(); ++it) {
        char key = it->first;
        GameCommand command = it->second;
        ss << key << ": " << commandToString(command) << std::endl;
    }
    return ss.str();
}

int ConsoleInput::requestInt(int min, int max, std::string msg) {
    std::string line;
    int i;
    while (true) {
        if (msg != "") {
            std::cout << msg << std::endl;
        }
        std::getline(std::cin, line);
        try {
            i = std::stoi(line);
        } catch (std::invalid_argument e) {
            continue;
        }
        if (i < min || i > max) {
            continue;
        }
        break;
    }
    return i;
}
