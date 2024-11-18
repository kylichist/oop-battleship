#include "../include/Player.hpp"

Player::Player(uint8_t fieldRows, uint8_t fieldColumns,
               std::map<uint8_t, uint8_t> shipScheme)
    : field(new Field(fieldRows, fieldColumns)),
      shipContainer(new ShipContainer(shipScheme)),
      playerParameters(new PlayerParameters()),
      abilityContainer(new AbilityContainer(*this)) {
    selectedCoodrinates = Coordinates();
}

void Player::resetSelectedCoordinates() {
    selectedCoodrinates.x = 0;
    selectedCoodrinates.y = 0;
}

Player::~Player() {
    delete field;
    delete shipContainer;
    delete abilityContainer;
    delete playerParameters;
}

Field& Player::getField() {
    return *field;
}

ShipContainer& Player::getShipContainer() {
    return *shipContainer;
}

Coordinates& Player::getSelectedCoordinates() {
    return selectedCoodrinates;
}

PlayerParameters& Player::getPlayerParameters() {
    return *playerParameters;
}

Player& Player::getEnemy() {
    return *enemy;
}

AbilityContainer& Player::getAbilityContainer() {
    return *abilityContainer;
}

void Player::setEnemy(Player* enemy) {
    this->enemy = enemy;
    enemy->getField().addObserver(abilityContainer);
}

void Player::resetIsAbilityUsed() {
    playerParameters->resetIsAbilityUsed();
}
