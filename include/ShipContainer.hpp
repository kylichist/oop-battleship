#ifndef SHIPCONTAINER_HPP  // SHIPCONTAINER_HPP
#define SHIPCONTAINER_HPP

#include <cstdint>
#include <map>

#include "Ship.hpp"

class ShipContainer {
private:
    std::vector<Ship*> ships;

public:
    ShipContainer(std::map<uint8_t, uint8_t> limits);
    uint8_t getShipsCount();
    uint8_t getAliveShipsCount();
    Ship& getShip(uint8_t index);
    ~ShipContainer();
};

#endif  // SHIPCONTAINER_HPP
