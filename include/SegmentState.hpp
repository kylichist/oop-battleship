#ifndef SEGMENTSTATE_HPP  // SEGMENTSTATE_HPP
#define SEGMENTSTATE_HPP

#include <cstdint>

enum class SegmentState : uint8_t { INTACT = 2, DAMAGED = 1, DESTROYED = 0 };

#endif  // SEGMENTSTATE_HPP
