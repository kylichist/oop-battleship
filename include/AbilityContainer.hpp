#ifndef ABILITYCONTAINER_HPP  // ABILITYCONTAINER_HPP
#define ABILITYCONTAINER_HPP

#include <deque>
#include <jsoncpp/json/json.h>

#include "Ability.hpp"
#include "Deserializer.hpp"
#include "FieldObserver.hpp"
#include "Serializer.hpp"

class Ability;
class Player;

class AbilityContainer : public FieldObserver {
private:
    std::deque<Ability*> abilities;
    std::vector<Ability*> getShuffledAbilities();
    Ability* getRandomAbility();
    Ability* getAbilityFromString(std::string string);
    friend class Serializer;
    friend class Deserializer;

public:
    AbilityContainer();
    uint8_t getAbilitiesCount();
    AbilityResult* useAbility(Player& player);
    std::string peek();
    void onShipDestroyed() override;
    ~AbilityContainer();
};

#endif  // ABILITYCONTAINER_HPP
