#ifndef FIELDPROVIDER_HPP  // FIELDPROVIDER_HPP
#define FIELDPROVIDER_HPP

#include "Field.hpp"
#include "ShipContainer.hpp"

class FieldProvider {
public:
    virtual void placeShips(Field& field, ShipContainer& shipContainer) = 0;

    virtual ~FieldProvider() {}
};

#endif  // FIELDPROVIDER_HPP
