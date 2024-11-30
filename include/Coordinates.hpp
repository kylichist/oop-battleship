#ifndef COORDINATES_HPP  // COORDINATES_HPP
#define COORDINATES_HPP

#include <cstdint>

struct Coordinates {
    int16_t x;
    int16_t y;

    Coordinates(int16_t x, int16_t y) : x(x), y(y) {}

    Coordinates() = default;
};

#endif  // COORDINATES_HPP
