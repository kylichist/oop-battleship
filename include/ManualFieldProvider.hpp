#ifndef MANUALFIELDPROVIDER_HPP  // MANUALFIELDPROVIDER_HPP
#define MANUALFIELDPROVIDER_HPP

#include "FieldProvider.hpp"

template <class Input, class Output>
class ManualFieldProvider : public FieldProvider {
private:
    Input& input;
    Output& output;

public:
    ManualFieldProvider(Input& input, Output& output)
        : input(input), output(output) {}

    void placeShips(Field& field, ShipContainer& shipContainer) override {
        uint8_t shipCount = shipContainer.getShipsCount();
        for (int16_t i = shipCount - 1; i >= 0; --i) {
            Ship& ship = shipContainer.getShip(i);
            bool placed = false;
            output.printMessage("Placing ship with length " +
                                std::to_string(ship.getLength()));
            while (!placed) {
                int16_t x = input.requestInt(0, field.getColumns() - 1,
                                             "Select x coordinate:");
                int16_t y = input.requestInt(0, field.getRows() - 1,
                                             "Select y coordinate:");
                bool isVertical = input.requestChoice("Vertical orientation?");
                Orientation orientation = static_cast<Orientation>(isVertical);
                Coordinates coordinates = {x, y};
                try {
                    field.setShip(coordinates, &ship, orientation);
                    placed = true;
                } catch (std::runtime_error e) {
                    output.printError(e);
                }
            }
        }
    }
};

#endif  // MANUALFIELDPROVIDER_HPP
