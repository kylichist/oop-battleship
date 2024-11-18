#ifndef SCANNERABILITY_HPP  // SCANNERABILITY_HPP
#define SCANNERABILITY_HPP

#include "Ability.hpp"

class ScannerAbility : public Ability {
public:
    AbilityResult* use(Player& player) override;
    std::string getName() override;
};

#endif  // SCANNERABILITY_HPP
