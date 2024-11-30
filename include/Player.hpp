#ifndef PLAYER_HPP  // PLAYER_HPP
#define PLAYER_HPP

#include <jsoncpp/json/json.h>

#include "AbilityContainer.hpp"
#include "Field.hpp"
#include "PlayerParameters.hpp"
#include "Serializer.hpp"
#include "ShipContainer.hpp"

class AbilityContainer;

class Player {
private:
    Field* field;
    ShipContainer* shipContainer;
    AbilityContainer* abilityContainer;
    Coordinates selectedCoodrinates;
    PlayerParameters* playerParameters;
    Player* enemy;
    friend class Serializer;

public:
    Player(Field* field, ShipContainer* shipContainer,
           AbilityContainer* abilityContainer,
           PlayerParameters* playerParameters);
    Field& getField();
    ShipContainer& getShipContainer();
    Coordinates& getSelectedCoordinates();
    PlayerParameters& getPlayerParameters();
    Player& getEnemy();
    AbilityContainer& getAbilityContainer();
    void setEnemy(Player* enemy);
    ~Player();
};

#endif  // PLAYER_HPP
