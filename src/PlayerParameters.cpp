#include "../include/PlayerParameters.hpp"

PlayerParameters::PlayerParameters() {
    resetAttackParameters();
    resetIsAbilityUsed();
}

uint8_t PlayerParameters::getDamage() {
    return damage;
}

void PlayerParameters::setDamage(uint8_t damage) {
    this->damage = damage;
}

void PlayerParameters::resetAttackParameters() {
    damage = 1;
}

bool PlayerParameters::getIsAbilityUsed() {
    return isAbilityUsed;
}

void PlayerParameters::setIsAbilityUsed(bool isAbilityUsed) {
    this->isAbilityUsed = isAbilityUsed;
}

void PlayerParameters::resetIsAbilityUsed() {
    isAbilityUsed = false;
}
