#include <cmath>
#include <iomanip>
#include <iostream>

#include "../include/ConsoleOutputHandler.hpp"

void ConsoleOutputHandler::printMessage(std::string message) {
    std::cout << message << std::endl;
}

void ConsoleOutputHandler::printField(Field& field, bool isEnemy) {
    Field printable = preprocessField(field);
    uint8_t rowsWidth = int(std::log10(printable.getRows()) + 1);
    uint8_t columnsWidth = int(std::log10(printable.getColumns()) + 1);

    std::cout << std::setw(columnsWidth) << " ";
    for (uint8_t i = 0; i < printable.getColumns(); ++i) {
        std::cout << " " << std::internal << std::setw(columnsWidth) << +i;
    }
    std::cout << std::endl;
    for (uint8_t y = 0; y < printable.getRows(); ++y) {
        std::cout << std::right << std::setw(rowsWidth) << +y;
        for (uint8_t x = 0; x < printable.getColumns(); ++x) {
            Tile tile = printable.getTile(x, y);
            std::cout << " " << std::internal << std::setw(columnsWidth);
            bool hidden = tile.tileState == TileState::HIDDEN;
            bool hasShip = tile.ship != nullptr;
            if (hidden && isEnemy) {
                std::cout << "H";
            }
            if (hidden && !isEnemy && !hasShip) {
                std::cout << "~";
            }
            if (hasShip && ((hidden && !isEnemy) || (!hidden))) {
                std::cout << static_cast<int>(
                    tile.ship->getSegment(printable.getSegmentIndex(x, y)));
            }
            if (!hidden && !hasShip) {
                std::cout << "X";
            }
        }
        std::cout << std::endl;
    }
}

void ConsoleOutputHandler::printOnTurnStart(Player& player) {
    printMessage("Your field:");
    printField(player.getField(), false);
    printMessage("\nEnemy field:");
    printField(player.getEnemy().getField(), true);
    printAbilitites(player.getAbilityContainer());
}

void ConsoleOutputHandler::printAbilitites(AbilityContainer& container) {
    printMessage("\nAvailable abilities: " +
                 std::to_string(container.getAbilitiesCount()));
    if (container.getAbilitiesCount() != 0) {
        printMessage("Front ability: " + container.peek());
    }
}

void ConsoleOutputHandler::printCoordinates(Coordinates coordinates) {
    printMessage("X: " + std::to_string(coordinates.x) +
                 ", Y: " + std::to_string(coordinates.y));
}
