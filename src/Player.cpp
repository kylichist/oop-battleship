#include "../include/Player.hpp"

Player::Player(Field* field, ShipContainer* shipContainer,
               AbilityContainer* abilityContainer,
               PlayerParameters* playerParameters)
    : field(field),
      shipContainer(shipContainer),
      playerParameters(playerParameters),
      abilityContainer(abilityContainer) {
    selectedCoodrinates = Coordinates();
}

Player::~Player() {
    if (field != nullptr) {
        delete field;
    }
    if (shipContainer != nullptr) {
        delete shipContainer;
    }
    if (abilityContainer != nullptr) {
        delete abilityContainer;
    }
    if (playerParameters != nullptr) {
        delete playerParameters;
    }
}

Field& Player::getField() {
    if (field == nullptr) {
        throw std::runtime_error("Trying to access null Field.");
    }
    return *field;
}

ShipContainer& Player::getShipContainer() {
    if (shipContainer == nullptr) {
        throw std::runtime_error("Trying to access null ShipContainer.");
    }
    return *shipContainer;
}

Coordinates& Player::getSelectedCoordinates() {
    return selectedCoodrinates;
}

PlayerParameters& Player::getPlayerParameters() {
    if (playerParameters == nullptr) {
        throw std::runtime_error("Trying to access null PlayerParameters.");
    }
    return *playerParameters;
}

Player& Player::getEnemy() {
    if (enemy == nullptr) {
        throw std::runtime_error("Trying to access null Player(enemy).");
    }
    return *enemy;
}

AbilityContainer& Player::getAbilityContainer() {
    if (abilityContainer == nullptr) {
        throw std::runtime_error("Trying to access null AbilityContainer.");
    }
    return *abilityContainer;
}

void Player::setEnemy(Player* enemy) {
    if (enemy == nullptr) {
        throw std::runtime_error("Trying to set null Player(enemy).");
    }

    this->enemy = enemy;
    if (abilityContainer != nullptr) {
        enemy->getField().addObserver(abilityContainer);
    }
}
