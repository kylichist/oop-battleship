#include <stdexcept>

#include "../include/ScannerAbility.hpp"

AbilityResult* ScannerAbility::use(Player& player) {
    Coordinates coordinates = player.getSelectedCoordinates();
    Field& enemyField = player.getEnemy().getField();

    if (coordinates.x >= enemyField.getColumns() ||
        coordinates.y >= enemyField.getRows()) {
        throw std::runtime_error("Coordinates are out of bounds");
    }

    if (coordinates.x == enemyField.getColumns() - 1) {
        coordinates.x -= 1;
    }
    if (coordinates.y == enemyField.getRows() - 1) {
        coordinates.y -= 1;
    }
    for (uint8_t ay = coordinates.y; ay <= coordinates.y + 1; ++ay) {
        for (uint8_t ax = coordinates.x; ax <= coordinates.x + 1; ++ax) {
            if (enemyField.getTile(ax, ay).ship != nullptr) {
                return new ScannerSuccessResult();
            }
        }
    }
    return new ScannerFailureResult();
}

std::string ScannerAbility::getName() {
    return "Scanner";
}
