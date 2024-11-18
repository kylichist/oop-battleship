#ifndef DOUBLEDAMAGEABILITY_HPP  // DOUBLEDAMAGEABILITY_HPP
#define DOUBLEDAMAGEABILITY_HPP

#include "Ability.hpp"

class DoubleDamageAbility : public Ability {
public:
    AbilityResult* use(Player& player) override;
    std::string getName() override;
};

#endif  // DOUBLEDAMAGEABILITY_HPP
