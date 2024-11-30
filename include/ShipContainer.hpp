#ifndef SHIPCONTAINER_HPP  // SHIPCONTAINER_HPP
#define SHIPCONTAINER_HPP

#include <cstdint>
#include <jsoncpp/json/json.h>
#include <map>

#include "Deserializer.hpp"
#include "Serializer.hpp"
#include "Ship.hpp"

class Ship;

class ShipContainer {
private:
    std::vector<Ship*> ships;
    std::map<uint8_t, uint8_t> limits;
    friend class Serializer;
    friend class Deserializer;

public:
    ShipContainer(std::map<uint8_t, uint8_t> limits);
    size_t getShipsCount();
    size_t getAliveShipsCount();
    Ship& getShip(uint8_t index);
    Ship& getShipById(int64_t id);
    std::map<uint8_t, uint8_t> getLimits();
    ~ShipContainer();
};

#endif  // SHIPCONTAINER_HPP
