#ifndef RANDOMFIELDPROVIDER_HPP  // RANDOMFIELDPROVIDER_HPP
#define RANDOMFIELDPROVIDER_HPP

#include "FieldProvider.hpp"
#include "RandomGenerator.hpp"

class RandomFieldProvider : public FieldProvider {
private:
    RandomGenerator randomGenerator;

public:
    RandomFieldProvider();
    void placeShips(Field& field, ShipContainer& shipContainer) override;
};

#endif  // RANDOMFIELDPROVIDER_HPP
