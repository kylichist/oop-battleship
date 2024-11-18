#ifndef ABILITYCONTAINER_HPP  // ABILITYCONTAINER_HPP
#define ABILITYCONTAINER_HPP

#include <queue>

#include "Ability.hpp"
#include "FieldObserver.hpp"

class Ability;
class Player;

class AbilityContainer : public FieldObserver {
private:
    Player& player;
    std::queue<Ability*> abilities;
    std::vector<Ability*> getShuffledAbilities();
    Ability* getRandomAbility();

public:
    AbilityContainer(Player& player);
    uint8_t getAbilitiesCount();
    AbilityResult* useAbility();
    std::string peek();
    void onShipDestroyed() override;
    ~AbilityContainer();
};

#endif  // ABILITYCONTAINER_HPP
