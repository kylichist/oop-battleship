#ifndef BOMBARDABILITY_HPP  // BOMBARDABILITY_HPP
#define BOMBARDABILITY_HPP

#include "Ability.hpp"

class BombardAbility : public Ability {
public:
    AbilityResult* use(Player& player) override;
    std::string getName() override;
};

#endif  // BOMBARDABILITY_HPP
