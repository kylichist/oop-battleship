#include <algorithm>
#include <stdexcept>

#include "../include/AbilityContainer.hpp"
#include "../include/BombardAbility.hpp"
#include "../include/DoubleDamageAbility.hpp"
#include "../include/NoAbilityAvailableException.hpp"
#include "../include/RandomGenerator.hpp"
#include "../include/ScannerAbility.hpp"

std::vector<Ability*> AbilityContainer::getShuffledAbilities() {
    std::vector<Ability*> availableAbilities = {
        new BombardAbility(), new ScannerAbility(), new DoubleDamageAbility()};

    std::shuffle(availableAbilities.begin(), availableAbilities.end(),
                 RandomGenerator().getGenerator());

    return availableAbilities;
}

Ability* AbilityContainer::getRandomAbility() {
    std::vector<Ability*> shuffledAbilities = getShuffledAbilities();
    uint8_t randomAbilityIndex =
        RandomGenerator().randomBetween(0, shuffledAbilities.size() - 1);

    Ability* ability = shuffledAbilities[randomAbilityIndex];
    for (size_t i = 0; i < shuffledAbilities.size(); ++i) {
        if (i != randomAbilityIndex) {
            delete shuffledAbilities[i];
        }
    }

    return ability;
}

AbilityContainer::AbilityContainer(Player& player) : player(player) {
    std::vector<Ability*> shuffledAbilities = getShuffledAbilities();

    for (uint8_t i = 0; i < shuffledAbilities.size(); ++i) {
        abilities.push(shuffledAbilities[i]);
    }
}

AbilityResult* AbilityContainer::useAbility() {
    if (abilities.size() == 0) {
        throw NoAbilityAvailableException();
    }

    Ability* ability = abilities.front();
    abilities.pop();

    uint8_t aliveShipsBefore = player.getShipContainer().getAliveShipsCount();
    AbilityResult* result = ability->use(player);
    uint8_t aliveShipsAfter = player.getShipContainer().getAliveShipsCount();
    if (aliveShipsAfter < aliveShipsBefore) {
        abilities.push(getRandomAbility());
    }

    delete ability;
    return result;
}

uint8_t AbilityContainer::getAbilitiesCount() {
    return abilities.size();
}

void AbilityContainer::onShipDestroyed() {
    abilities.push(getRandomAbility());
}

AbilityContainer::~AbilityContainer() {
    uint8_t abilitiesSize = abilities.size();
    for (uint8_t i = 0; i < abilitiesSize; ++i) {
        Ability* ability = abilities.front();
        abilities.pop();
        delete ability;
    }
}

std::string AbilityContainer::peek() {
    return abilities.front()->getName();
}
