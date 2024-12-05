#ifndef CONSOLEINPUT_HPP  // CONSOLEINPUT_HPP
#define CONSOLEINPUT_HPP

#include <map>
#include <string>

#include "Coordinates.hpp"
#include "GameCommand.hpp"

#define COMMANDS_COUNT 10

using ControlConfiguration = std::map<char, GameCommand>;

class ConsoleInput {
private:
    ControlConfiguration config;

public:
    ConsoleInput();
    std::string getInfo();
    GameCommand requestCommand(std::string msg = "");
    bool requestChoice(std::string msg = "");
    std::string requestString(std::string msg = "");
    int requestInt(int min, int max, std::string msg = "");
    void loadConfiguration(ControlConfiguration config);
};

#endif  // CONSOLEINPUT_HPP
