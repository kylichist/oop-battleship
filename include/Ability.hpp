#ifndef ABILITY_HPP  // ABILITY_HPP
#define ABILITY_HPP

#include <string>

#include "AbilityResult.hpp"
#include "Player.hpp"

class Player;

class Ability {
public:
    virtual AbilityResult* use(Player& player) = 0;
    virtual std::string getName() = 0;

    virtual ~Ability() {}
};

#endif  // ABILITY_HPP
