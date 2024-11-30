#ifndef FIELD_HPP  // FIELD_HPP
#define FIELD_HPP

#include <cstdint>
#include <jsoncpp/json/json.h>
#include <vector>

#include "Coordinates.hpp"
#include "Deserializer.hpp"
#include "FieldObserver.hpp"
#include "Orientation.hpp"
#include "Serializer.hpp"
#include "ShipContainer.hpp"
#include "Tile.hpp"

class Field {
private:
    uint8_t rows;
    uint8_t columns;
    std::vector<FieldObserver*> observers;
    std::vector<std::vector<Tile>> tiles;
    void setTile(Coordinates coordinates, Tile tile);
    void setTile(uint8_t x, uint8_t y, Tile tile);
    friend class Serializer;
    friend class Deserializer;

public:
    Field(uint8_t rows, uint8_t columns);
    Field(const Field& other);             // копирование
    Field& operator=(const Field& other);  // копирование
    Field(Field&& other);                  // перемещение
    Field& operator=(Field&& other);       // перемещение
    uint8_t getRows();
    uint8_t getColumns();
    Tile getTile(Coordinates coordinates);
    Tile getTile(uint8_t x, uint8_t y);
    uint8_t getSegmentIndex(Coordinates coordinates);
    uint8_t getSegmentIndex(uint8_t x, uint8_t y);
    void setTileState(Coordinates coordinates, TileState tileState);
    void setShip(Coordinates coordinates, Ship* ship, Orientation orientation);
    bool checkCoordinates(Coordinates coordinates);
    bool checkCoordinates(int16_t x, int16_t y);
    void shootAt(Coordinates coordinates, uint8_t damage);
    void addObserver(FieldObserver* observer);
};

#endif  // FIELD_HPP
