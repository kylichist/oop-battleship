#ifndef SERIALIZER_HPP  // SERIALIZER_HPP
#define SERIALIZER_HPP

#include <jsoncpp/json/json.h>

#include "AbilityContainer.hpp"
#include "Field.hpp"
#include "GameState.hpp"
#include "PlayerParameters.hpp"
#include "Ship.hpp"
#include "ShipContainer.hpp"
#include "Tile.hpp"

#define SAVEFILE_VERSION 1

class Ship;
class ShipContainer;
class PlayerParameters;
class Field;
class AbilityContainer;
class Player;
class GameState;

class Serializer {
public:
    Json::Value serializeShip(Ship* ship);
    Json::Value serializeShipContainer(ShipContainer* shipContainer);
    Json::Value serializePlayerParameters(PlayerParameters* playerParameters);
    Json::Value serializeTile(Tile tile);
    Json::Value serializeField(Field* field);
    Json::Value serializeAbilityContainer(AbilityContainer* abilityContainer);
    Json::Value serializePlayer(Player* player);
    Json::Value serializeGameState(GameState* gameState);
};

#endif  // SERIALIZER_HPP
