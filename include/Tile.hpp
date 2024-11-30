#ifndef TILE_HPP  // TILE_HPP
#define TILE_HPP

#include <jsoncpp/json/json.h>

#include "Serializer.hpp"
#include "Ship.hpp"
#include "TileState.hpp"

class Ship;

struct Tile {
private:
    friend class Serializer;

public:
    Ship* ship;
    TileState tileState;

    Tile(Ship* ship = nullptr, TileState tileState = TileState::HIDDEN)
        : ship(ship), tileState(tileState) {}
};

#endif  // TILE_HPP
