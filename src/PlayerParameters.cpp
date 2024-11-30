#include "../include/PlayerParameters.hpp"

PlayerParameters::PlayerParameters() {
    resetAll();
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

void PlayerParameters::resetAll() {
    resetIsAbilityUsed();
    resetAttackParameters();
}
