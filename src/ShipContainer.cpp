#include <algorithm>
#include <stdexcept>

#include "../include/ShipContainer.hpp"

ShipContainer::ShipContainer(std::map<uint8_t, uint8_t> limits) {
    this->ships = std::vector<Ship*>();
    this->limits = limits;
    for (auto pair : limits) {
        // (length, count)
        for (uint8_t count = 0; count < pair.second; ++count) {
            ships.push_back(new Ship(pair.first));
        }
    };
}

size_t ShipContainer::getShipsCount() {
    return ships.size();
}

Ship& ShipContainer::getShip(uint8_t index) {
    if (index >= ships.size()) {
        throw std::runtime_error("Ship index out of bounds.");
    }
    return *ships[index];
}

Ship& ShipContainer::getShipById(int64_t id) {
    int64_t index = -1;
    for (size_t i = 0; i < ships.size(); ++i) {
        if (ships[i]->getId() == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        throw std::runtime_error("No ship with specified ID");
    }
    return *ships[index];
}

ShipContainer::~ShipContainer() {
    for (size_t i = 0; i < ships.size(); ++i) {
        delete ships[i];
    }
}

size_t ShipContainer::getAliveShipsCount() {
    return std::count_if(ships.begin(), ships.end(),
                         [](Ship* ship) { return !ship->isDestroyed(); });
}

std::map<uint8_t, uint8_t> ShipContainer::getLimits() {
    return limits;
}
