#include <stdexcept>

#include "../include/RandomGenerator.hpp"
#include "../include/Ship.hpp"

Ship::Ship(uint8_t length) {
    if (length == 0 || length > 4) {
        throw std::runtime_error("Improper ship length.");
    }
    this->segments = std::vector<uint8_t>();
    for (uint8_t i = 0; i < length; ++i) {
        segments.push_back(2);
    }
    this->id = RandomGenerator().randomId();
}

uint8_t Ship::getLength() {
    return segments.size();
}

int64_t Ship::getId() {
    return id;
}

SegmentState Ship::getSegment(uint8_t segmentIndex) {
    if (!checkSegmentIndex(segmentIndex)) {
        throw std::runtime_error("Segment index out of bounds.");
    }

    return static_cast<SegmentState>(segments[segmentIndex]);
}

void Ship::damageSegment(uint8_t segmentIndex, uint8_t damage) {
    if (!checkSegmentIndex(segmentIndex)) {
        throw std::runtime_error("Segment index out of bounds.");
    }

    if (getSegment(segmentIndex) == SegmentState::DESTROYED) {
        return;
    }

    if (segments[segmentIndex] < damage) {
        segments[segmentIndex] = 0;
    } else {
        segments[segmentIndex] -= damage;
    }
}

bool Ship::checkSegmentIndex(uint8_t segmentIndex) {
    return segmentIndex < getLength();
}

bool Ship::isDestroyed() {
    bool destroyed = true;
    for (uint8_t i = 0; i < getLength(); ++i) {
        if (segments[i] != 0) {
            destroyed = false;
            break;
        }
    }
    return destroyed;
}
