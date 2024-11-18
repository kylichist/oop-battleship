#ifndef OUTPUTHANDLER_HPP  // OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP

#include <string>

#include "Field.hpp"
#include "Player.hpp"

class OutputHandler {
protected:
    Field preprocessField(Field& field);

public:
    virtual void printMessage(std::string message) = 0;
    virtual void printField(Field& field, bool isEnemy) = 0;
    virtual void printOnTurnStart(Player& player) = 0;
    virtual void printAbilitites(AbilityContainer& container) = 0;
    virtual void printCoordinates(Coordinates coordinates) = 0;

    virtual ~OutputHandler() {}
};

#endif  // OUTPUTHANDLER_HPP
