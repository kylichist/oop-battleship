#ifndef SHIP_HPP  // SHIP_HPP
#define SHIP_HPP

#include <cstdint>
#include <vector>

#include "SegmentState.hpp"

class Ship {
private:
    std::vector<uint8_t> segments;

public:
    Ship(uint8_t length);
    uint8_t getLength();
    SegmentState getSegment(uint8_t segmentIndex);
    void damageSegment(uint8_t segmentIndex, uint8_t damage);
    bool isDestroyed();
    bool checkSegmentIndex(uint8_t segmentIndex);
};

#endif  // SHIP_HPP
