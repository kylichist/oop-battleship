#ifndef CONSOLEOUTPUT_HPP  // CONSOLEOUTPUT_HPP
#define CONSOLEOUTPUT_HPP

#include <stdexcept>
#include <string>

#include "Field.hpp"

class ConsoleOutput {
public:
    void printField(Field& field, bool isEnemy = false);
    void printMessage(std::string message);
    void printError(std::runtime_error error);
    void printError(std::exception error);
};

#endif  // CONSOLEOUTPUT_HPP
