#ifndef COORDINATES_HPP  // COORDINATES_HPP
#define COORDINATES_HPP

#include <cstdint>

struct Coordinates {
    uint8_t x;
    uint8_t y;

    Coordinates(uint8_t x, uint8_t y) : x(x), y(y) {}

    Coordinates() = default;
};

#endif  // COORDINATES_HPP
