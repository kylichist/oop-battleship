#include <vector>

#include "../include/BombardAbility.hpp"
#include "../include/RandomGenerator.hpp"

AbilityResult* BombardAbility::use(Player& player) {
    ShipContainer& shipContainer = player.getEnemy().getShipContainer();
    std::vector<uint8_t> remainingShips = {};
    for (uint8_t i = 0; i < shipContainer.getShipsCount(); ++i) {
        Ship& ship = shipContainer.getShip(i);
        if (!ship.isDestroyed()) {
            remainingShips.push_back(i);
        }
    }
    if (remainingShips.size() == 0) {
        return new BombardFailureResult();
    }

    RandomGenerator randomGenerator = RandomGenerator();
    uint8_t randomShipIndex =
        randomGenerator.randomBetween(0, remainingShips.size() - 1);

    Ship& ship = shipContainer.getShip(randomShipIndex);
    std::vector<uint8_t> remainingSegments = {};

    for (uint8_t j = 0; j < ship.getLength(); ++j) {
        if (ship.getSegment(j) != SegmentState::DESTROYED) {
            remainingSegments.push_back(j);
        }
    }

    uint8_t randomSegmentIndex =
        randomGenerator.randomBetween(0, remainingSegments.size() - 1);

    ship.damageSegment(remainingSegments[randomSegmentIndex], 1);
    if (ship.isDestroyed()) {
        return new BombardShipDestroyedResult();
    }
    return new BombardSuccessResult();
}

std::string BombardAbility::getName() {
    return "Bombard";
}
