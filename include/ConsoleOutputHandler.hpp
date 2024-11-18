#ifndef CONSOLEOUTPUTHANDLER_HPP  // CONSOLEOUTPUTHANDLER_HPP
#define CONSOLEOUTPUTHANDLER_HPP

#include "OutputHandler.hpp"

class ConsoleOutputHandler : public OutputHandler {
public:
    ConsoleOutputHandler() {}

    void printMessage(std::string message) override;
    void printField(Field& field, bool isEnemy) override;
    void printOnTurnStart(Player& player) override;
    void printAbilitites(AbilityContainer& container) override;
    void printCoordinates(Coordinates coordinates) override;
};

#endif  // CONSOLEOUTPUTHANDLER_HPP
