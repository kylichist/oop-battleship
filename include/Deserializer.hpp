#ifndef DESERIALIZER_HPP  // DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include <jsoncpp/json/json.h>

#include "AbilityContainer.hpp"
#include "Field.hpp"
#include "GameState.hpp"
#include "PlayerParameters.hpp"
#include "Ship.hpp"
#include "ShipContainer.hpp"

class Ship;
class ShipContainer;
class PlayerParameters;
class Field;
class AbilityContainer;

class Deserializer {
public:
    Ship* deserializeShip(Json::Value object);
    ShipContainer* deserializeShipContainer(Json::Value object);
    PlayerParameters* deserializePlayerParameters(Json::Value object);
    Field* deserializeField(Json::Value object, ShipContainer& shipContainer);
    AbilityContainer* deserializeAbilityContainer(Json::Value object);
    void deserializeGameState(Json::Value object, GameState& gameState);
};
#endif  // DESERIALIZER_HPP