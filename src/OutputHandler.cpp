#include <stdexcept>

#include "../include/OutputHandler.hpp"

Field OutputHandler::preprocessField(Field& field) {
    Field processed = field;
    for (uint8_t y = 0; y < processed.getRows(); ++y) {
        for (uint8_t x = 0; x < processed.getColumns(); ++x) {
            Tile tile = processed.getTile(x, y);
            if (tile.ship != nullptr && tile.ship->isDestroyed()) {
                for (int16_t sy = y - 1; sy <= y + 1; ++sy) {
                    for (int16_t sx = x - 1; sx <= x + 1; ++sx) {
                        try {
                            processed.setTileState(Coordinates(sx, sy),
                                                   TileState::SHOT);
                        } catch (std::runtime_error e) {}
                    }
                }
            }
        }
    }
    return processed;
}
