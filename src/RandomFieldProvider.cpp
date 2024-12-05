#include <stdexcept>

#include "../include/RandomFieldProvider.hpp"

#define TRY_LIMIT 1000

RandomFieldProvider::RandomFieldProvider() {
    randomGenerator = RandomGenerator();
}

void RandomFieldProvider::placeShips(Field& field,
                                     ShipContainer& shipContainer) {
    uint8_t shipCount = shipContainer.getShipsCount();
    for (int16_t i = shipCount - 1; i >= 0; --i) {
        Ship& ship = shipContainer.getShip(i);
        bool placed = false;
        int tries = 0;
        while (!placed) {
            tries += 1;
            if (tries >= TRY_LIMIT) {
                throw std::runtime_error("Could not place ships randomly.");
            }
            Orientation orientation =
                static_cast<Orientation>(randomGenerator.randomBetween(0, 1));
            uint8_t randomX = randomGenerator.randomBetween(
                0, field.getColumns() - (orientation == Orientation::HORIZONTAL
                                             ? ship.getLength()
                                             : 1));
            uint8_t randomY = randomGenerator.randomBetween(
                0, field.getRows() - (orientation == Orientation::VERTICAL
                                          ? ship.getLength()
                                          : 1));
            Coordinates coordinates = {randomX, randomY};
            try {
                field.setShip(coordinates, &ship, orientation);
                placed = true;
            } catch (std::runtime_error e) {}
        }
    }
}
