#include <stdexcept>

#include "../include/AttackOutOfBounds.hpp"
#include "../include/Field.hpp"
#include "../include/ShipPlacementException.hpp"

Field::Field(uint8_t rows, uint8_t columns) : rows(rows), columns(columns) {
    if (rows == 0 || columns == 0) {
        throw std::runtime_error(
            "Improper field size.");  // выбрасывается ошибка в случае передачи нуля как размера поля
    }
    observers = {};
    // заполнение двумерных векторов клеток значениями по умолчанию
    tiles = std::vector<std::vector<Tile>>();
    for (size_t i = 0; i < rows; ++i) {
        tiles.push_back(std::vector<Tile>());
        for (size_t j = 0; j < columns; ++j) {
            tiles[i].push_back(Tile());
        }
    }
}

Field::Field(const Field& other)
    : rows(other.rows),
      columns(other.columns),
      tiles(other.tiles),
      observers(other.observers) {}

//копирование

Field& Field::operator=(const Field& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        tiles = other.tiles;
        observers = other.observers;
    }
    return *this;
}  // копирование

Field::Field(Field&& other)
    : rows(other.rows),
      columns(other.columns),
      tiles(other.tiles),
      observers(other.observers) {
    other.rows = 0;
    other.columns = 0;
    other.tiles.clear();
    other.observers.clear();
}  // перемещение

Field& Field::operator=(Field&& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        tiles = other.tiles;
        observers = other.observers;
        other.rows = 0;
        other.columns = 0;
        other.tiles.clear();
        other.observers.clear();
    }
    return *this;
}  // перемещение

uint8_t Field::getRows() {
    return rows;
}

uint8_t Field::getColumns() {
    return columns;
}

Tile Field::getTile(Coordinates coordinates) {
    if (!checkCoordinates(coordinates)) {
        throw std::runtime_error("Coordinates are out of bounds.");
    }

    return tiles[coordinates.y][coordinates.x];
}

Tile Field::getTile(uint8_t x, uint8_t y) {
    return getTile(Coordinates(x, y));
}

uint8_t Field::getSegmentIndex(Coordinates coordinates) {
    if (!checkCoordinates(coordinates)) {
        throw std::runtime_error("Coordinates are out of bounds.");
    }
    if (getTile(coordinates).ship == nullptr) {
        throw std::runtime_error("No ship on the coordinates.");
    }
    uint8_t segmentIndex = 0;
    int16_t x = coordinates.x - 1, y = coordinates.y - 1;

    while (checkCoordinates(x, coordinates.y) &&
           getTile(x, coordinates.y).ship != nullptr) {
        segmentIndex += 1;
        x -= 1;
    }
    while (checkCoordinates(coordinates.x, y) &&
           getTile(coordinates.x, y).ship != nullptr) {
        segmentIndex += 1;
        y -= 1;
    }
    return segmentIndex;
}

uint8_t Field::getSegmentIndex(uint8_t x, uint8_t y) {
    return getSegmentIndex(Coordinates(x, y));
}

void Field::setTile(Coordinates coordinates, Tile tile) {
    if (!checkCoordinates(coordinates)) {
        throw std::runtime_error("Coordinates are out of bounds.");
    }
    tiles[coordinates.y][coordinates.x] = tile;
}

void Field::setTile(uint8_t x, uint8_t y, Tile tile) {
    setTile(Coordinates(x, y), tile);
}

void Field::setTileState(Coordinates coordinates, TileState tileState) {
    if (!checkCoordinates(coordinates)) {
        throw std::runtime_error("Coordinates are out of bounds.");
    }

    tiles[coordinates.y][coordinates.x].tileState = tileState;
}

void Field::setShip(Coordinates coordinates, Ship* ship,
                    Orientation orientation) {
    if (ship == nullptr) {
        throw std::runtime_error("Ship is null");
    }
    bool isHorizontal = orientation == Orientation::HORIZONTAL;
    if (isHorizontal && ship->getLength() > columns) {
        throw std::runtime_error("Field is less than ship.");
    }
    if (!isHorizontal && ship->getLength() > rows) {
        throw std::runtime_error("Field is less than ship.");
    }
    int16_t shipHeadX = coordinates.x, shipHeadY = coordinates.y;
    int16_t shipTailX =
        isHorizontal ? shipHeadX + ship->getLength() - 1 : shipHeadX;
    int16_t shipTailY =
        isHorizontal ? shipHeadY : shipHeadY + ship->getLength() - 1;

    int16_t regionStartX = shipHeadX - 1, regionStartY = shipHeadY - 1,
            regionEndX = shipTailX + 1, regionEndY = shipTailY + 1;

    bool checkHead = checkCoordinates(Coordinates(shipHeadX, shipHeadY)),
         checkTail = checkCoordinates(Coordinates(shipTailX, shipTailY));

    // проверка, что коордианыт носа и кормы корабля внутри поля, иначе размещение невозможно
    if (!(checkHead && checkTail)) {
        throw ShipPlacementException(shipHeadX, shipHeadY);
    }

    // проверка, что в "радиусе" одной клетки от корабля, который мы хотим поставить, нет других кораблей
    for (int16_t y = regionStartY; y <= regionEndY; ++y) {
        for (int16_t x = regionStartX; x <= regionEndX; ++x) {
            if (!checkCoordinates(x, y)) {
                continue;  // если координаты точки за пределами поля, то они не участвуют в определении корректности размещения
            }
            Tile tile = getTile(x, y);
            if (tile.ship != nullptr) {
                throw ShipPlacementException(x, y);
                // выбрасывается ошибка, если рядом с кораблем есть другие корабли
            }
        }
    }

    //размещение корабля
    if (isHorizontal) {
        for (uint8_t sx = shipHeadX; sx <= shipTailX; ++sx) {
            setTile(Coordinates(sx, shipHeadY), Tile(ship));
        }
    } else {
        for (uint8_t sy = shipHeadY; sy <= shipTailY; ++sy) {
            setTile(Coordinates(shipHeadX, sy), Tile(ship));
        }
    }
}

bool Field::checkCoordinates(Coordinates coordinates) {
    return coordinates.x >= 0 && coordinates.x < columns &&
           coordinates.y >= 0 && coordinates.y < rows;
}

bool Field::checkCoordinates(int16_t x, int16_t y) {
    return checkCoordinates(Coordinates(x, y));
}

void Field::shootAt(Coordinates coordinates, uint8_t damage) {
    if (!checkCoordinates(coordinates)) {
        throw AttackOutOfBounds(coordinates.x, coordinates.y);
    }
    setTileState(coordinates, TileState::SHOT);
    Tile tile = getTile(coordinates);
    if (tile.ship == nullptr) {
        return;
    }
    uint8_t segmentIndex = getSegmentIndex(coordinates);
    if (tile.ship->getSegment(segmentIndex) == SegmentState::DESTROYED) {
        return;
    }
    tile.ship->damageSegment(segmentIndex, damage);
    if (tile.ship->isDestroyed()) {
        for (auto observer : observers) {
            observer->onShipDestroyed();
        }

        int16_t x = coordinates.x - 1, y = coordinates.y - 1;

        bool left = checkCoordinates(coordinates.x - 1, coordinates.y) &&
                    getTile(coordinates.x - 1, coordinates.y).ship != nullptr;
        bool right = checkCoordinates(coordinates.x + 1, coordinates.y) &&
                     getTile(coordinates.x + 1, coordinates.y).ship != nullptr;
        bool horizontal = left || right;

        while (checkCoordinates(x, coordinates.y) &&
               getTile(x, coordinates.y).ship != nullptr) {
            x -= 1;
        }
        while (checkCoordinates(coordinates.x, y) &&
               getTile(coordinates.x, y).ship != nullptr) {
            y -= 1;
        }

        int16_t xe = 0, ye = 0;
        if (horizontal) {
            xe = x + tile.ship->getLength() + 1;
            ye = y + 2;
        } else {
            ye = y + tile.ship->getLength() + 1;
            xe = x + 2;
        }

        for (int16_t sy = y; sy <= ye; ++sy) {
            for (int16_t sx = x; sx <= xe; ++sx) {
                Coordinates tc = Coordinates(sx, sy);
                if (checkCoordinates(tc)) {
                    setTileState(tc, TileState::SHOT);
                }
            }
        }
    }
}

void Field::addObserver(FieldObserver* observer) {
    if (observer == nullptr) {
        return;
    }
    observers.push_back(observer);
}
