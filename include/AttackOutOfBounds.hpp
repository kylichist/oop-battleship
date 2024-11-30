#ifndef ATTACKOUTOFBOUNDS_HPP  // ATTACKOUTOFBOUNDS_HPP
#define ATTACKOUTOFBOUNDS_HPP

#include <stdexcept>

#include "Coordinates.hpp"

class AttackOutOfBounds : public std::runtime_error {
private:
    int16_t x;
    int16_t y;

public:
    AttackOutOfBounds(int16_t x, int16_t y)
        : runtime_error("Attack out of bounds at x: " + std::to_string(x) +
                        ", y: " + std::to_string(y)),
          x(x),
          y(y) {}

    Coordinates getCoordinates() { return Coordinates(x, y); }
};
#endif  // ATTACKOUTOFBOUNDS_HPP
