#include "../include/DoubleDamageAbility.hpp"

AbilityResult* DoubleDamageAbility::use(Player& player) {
    PlayerParameters& playerParameters = player.getPlayerParameters();
    playerParameters.setDamage(2);
    return new DoubleDamageSuccessResult();
}

std::string DoubleDamageAbility::getName() {
    return "Double Damage";
}
