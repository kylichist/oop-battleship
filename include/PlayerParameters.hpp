#ifndef PLAYERPARAMETERS_HPP  // PLAYERPARAMETERS_HPP
#define PLAYERPARAMETERS_HPP

#include <cstdint>

class PlayerParameters {
private:
    uint8_t damage;
    bool isAbilityUsed;

public:
    PlayerParameters();

    uint8_t getDamage();
    void setDamage(uint8_t damage);
    void resetAttackParameters();
    bool getIsAbilityUsed();
    void setIsAbilityUsed(bool isAbilityUsed);
    void resetIsAbilityUsed();
};

#endif  // PLAYERPARAMETERS_HPP
