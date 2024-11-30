#ifndef SHIP_HPP  // SHIP_HPP
#define SHIP_HPP

#include <cstdint>
#include <jsoncpp/json/json.h>
#include <vector>

#include "Deserializer.hpp"
#include "SegmentState.hpp"
#include "Serializer.hpp"

class Ship {
private:
    std::vector<uint8_t> segments;
    int64_t id;
    friend class Serializer;
    friend class Deserializer;

public:
    Ship(uint8_t length);
    uint8_t getLength();
    int64_t getId();
    SegmentState getSegment(uint8_t segmentIndex);
    void damageSegment(uint8_t segmentIndex, uint8_t damage);
    bool isDestroyed();
    bool checkSegmentIndex(uint8_t segmentIndex);
};

#endif  // SHIP_HPP
