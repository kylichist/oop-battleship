#ifndef TILE_HPP  // TILE_HPP
#define TILE_HPP

#include "Ship.hpp"
#include "TileState.hpp"

struct Tile {
    Ship* ship;
    TileState tileState;

    Tile(Ship* ship = nullptr, TileState tileState = TileState::HIDDEN)
        : ship(ship), tileState(tileState) {}
};

#endif  // TILE_HPP
