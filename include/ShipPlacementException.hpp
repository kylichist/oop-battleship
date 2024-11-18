#ifndef SHIPPLACEMENTEXCEPTION_HPP  // SHIPPLACEMENTEXCEPTION_HPP
#define SHIPPLACEMENTEXCEPTION_HPP

#include <stdexcept>

#include "Coordinates.hpp"

class ShipPlacementException : public std::runtime_error {
private:
    uint8_t x;
    uint8_t y;

public:
    ShipPlacementException(uint8_t x, uint8_t y)
        : runtime_error("Wrong ship placement at x: " + std::to_string(x) +
                        ", y: " + std::to_string(y)),
          x(x),
          y(y) {}

    Coordinates getCoordinates() { return Coordinates(x, y); }
};

#endif  // SHIPPLACEMENTEXCEPTION_HPP
