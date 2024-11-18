#include <algorithm>
#include <stdexcept>

#include "../include/ShipContainer.hpp"

ShipContainer::ShipContainer(std::map<uint8_t, uint8_t> limits) {
    this->ships = std::vector<Ship*>();
    for (auto pair : limits) {
        for (uint8_t count = 0; count < pair.second; ++count) {
            ships.push_back(new Ship(pair.first));
        }
    };
}

uint8_t ShipContainer::getShipsCount() {
    return ships.size();
}

Ship& ShipContainer::getShip(uint8_t index) {
    if (index >= ships.size()) {
        throw std::runtime_error("Ship index out of bounds.");
    }
    return *ships[index];
}

ShipContainer::~ShipContainer() {
    for (uint8_t i = 0; i < ships.size(); ++i) {
        delete ships[i];
    }
}

uint8_t ShipContainer::getAliveShipsCount() {
    return std::count_if(ships.begin(), ships.end(),
                         [](Ship* ship) { return !ship->isDestroyed(); });
}
