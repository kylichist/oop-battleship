#include "../include/Serializer.hpp"

Json::Value Serializer::serializeShip(Ship* ship) {
    Json::Value object = Json::Value();
    object["id"] = ship->id;
    for (uint8_t i = 0; i < ship->segments.size(); ++i) {
        object["segments"][i] = ship->segments[i];
    }
    return object;
}

Json::Value Serializer::serializeShipContainer(ShipContainer* shipContainer) {
    Json::Value object = Json::Value();
    for (int i = 0; i < shipContainer->ships.size(); ++i) {
        object["ships"][i] = serializeShip(shipContainer->ships[i]);
    }
    return object;
}

Json::Value Serializer::serializePlayerParameters(
    PlayerParameters* playerParameters) {
    Json::Value object = Json::Value();
    object["damage"] = playerParameters->damage;
    object["isAbilityUsed"] = playerParameters->isAbilityUsed;
    return object;
}

Json::Value Serializer::serializeTile(Tile tile) {
    Json::Value object = Json::Value();
    object["tileState"] = static_cast<int>(tile.tileState);
    if (tile.ship == nullptr) {
        object["shipId"] = Json::nullValue;
    } else {
        object["shipId"] = tile.ship->getId();
    }
    return object;
}

Json::Value Serializer::serializeField(Field* field) {
    Json::Value object = Json::Value();
    object["rows"] = field->rows;
    object["columns"] = field->columns;
    for (size_t i = 0; i < field->rows; ++i) {
        for (size_t j = 0; j < field->columns; ++j) {
            int index = i * field->rows + j;
            object["tiles"][index] = serializeTile(field->tiles[i][j]);
        }
    }
    return object;
}

Json::Value Serializer::serializeAbilityContainer(
    AbilityContainer* abilityContainer) {
    Json::Value object = Json::Value();
    object["abilities"] = Json::arrayValue;
    for (int i = 0; i < abilityContainer->abilities.size(); ++i) {
        object["abilities"][i] = abilityContainer->abilities[i]->getName();
    }
    return object;
}

Json::Value Serializer::serializePlayer(Player* player) {
    Json::Value object = Json::Value();
    if (player->playerParameters != nullptr) {
        object["playerParameters"] =
            serializePlayerParameters(player->playerParameters);
    }
    if (player->shipContainer != nullptr) {
        object["shipContainer"] = serializeShipContainer(player->shipContainer);
    }
    if (player->field != nullptr) {
        object["field"] = serializeField(player->field);
    }
    if (player->abilityContainer != nullptr) {
        object["abilityContainer"] =
            serializeAbilityContainer(player->abilityContainer);
    }
    return object;
}

Json::Value Serializer::serializeGameState(GameState* gameState) {
    Json::Value game = Json::Value();
    game["players"][0] = serializePlayer(gameState->user);
    game["players"][1] = serializePlayer(gameState->bot);
    size_t hash = std::hash<std::string>()(game.toStyledString());

    Json::Value object = Json::Value();
    object["hash"] = hash;
    object["version"] = SAVEFILE_VERSION;
    object["game"] = game;
    return object;
}
