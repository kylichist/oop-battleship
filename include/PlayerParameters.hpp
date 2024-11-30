#ifndef PLAYERPARAMETERS_HPP  // PLAYERPARAMETERS_HPP
#define PLAYERPARAMETERS_HPP

#include <cstdint>
#include <jsoncpp/json/json.h>

#include "Deserializer.hpp"
#include "Serializer.hpp"

class PlayerParameters {
private:
    uint8_t damage;
    bool isAbilityUsed;
    friend class Serializer;
    friend class Deserializer;

public:
    PlayerParameters();
    uint8_t getDamage();
    void setDamage(uint8_t damage);
    void resetAttackParameters();
    bool getIsAbilityUsed();
    void setIsAbilityUsed(bool isAbilityUsed);
    void resetIsAbilityUsed();
    void resetAll();
};

#endif  // PLAYERPARAMETERS_HPP
