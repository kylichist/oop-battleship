#include "../include/Deserializer.hpp"

Ship* Deserializer::deserializeShip(Json::Value object) {
    uint8_t length = object["segments"].size();
    Ship* ship = new Ship(length);

    ship->id = object["id"].asInt64();

    ship->segments.clear();
    for (uint8_t i = 0; i < object["segments"].size(); ++i) {
        ship->segments.push_back(object["segments"][i].asUInt());
    }
    return ship;
}

ShipContainer* Deserializer::deserializeShipContainer(Json::Value object) {
    std::map<uint8_t, uint8_t> blankLimits = {};
    ShipContainer* shipContainer = new ShipContainer(blankLimits);

    Json::Value shipsArray = object["ships"];
    std::map<uint8_t, uint8_t> limits = {};

    for (size_t i = 0; i < shipsArray.size(); ++i) {
        Ship* ship = deserializeShip(shipsArray[(int)i]);
        shipContainer->ships.push_back(ship);

        uint8_t length = ship->getLength();
        if (limits.count(length) == 0) {
            limits[length] = 1;
        } else {
            limits[length] += 1;
        }
    }
    shipContainer->limits = limits;
    return shipContainer;
}

PlayerParameters* Deserializer::deserializePlayerParameters(
    Json::Value object) {
    PlayerParameters* playerParameters = new PlayerParameters();
    playerParameters->damage = object["damage"].asUInt();
    playerParameters->isAbilityUsed = object["isAbilityUsed"].asBool();
    return playerParameters;
}

Field* Deserializer::deserializeField(Json::Value object,
                                      ShipContainer& shipContainer) {
    uint8_t rows = object["rows"].asUInt();
    uint8_t columns = object["columns"].asUInt();
    Field* field = new Field(rows, columns);

    field->tiles.clear();
    Json::Value tilesArray = object["tiles"];

    for (size_t i = 0; i < rows; ++i) {
        field->tiles.push_back(std::vector<Tile>());
        for (size_t j = 0; j < columns; ++j) {
            int index = i * rows + j;
            TileState tileState =
                static_cast<TileState>(tilesArray[index]["tileState"].asInt());
            Ship* ship = nullptr;
            if (!tilesArray[index]["shipId"].isNull()) {
                ship = &shipContainer.getShipById(
                    tilesArray[index]["shipId"].asInt64());
            }
            field->tiles[i].push_back(Tile(ship, tileState));
        }
    }
    return field;
}

AbilityContainer* Deserializer::deserializeAbilityContainer(
    Json::Value object) {
    AbilityContainer* abilityContainer = new AbilityContainer();

    uint8_t abilitiesSize = abilityContainer->abilities.size();
    for (uint8_t i = 0; i < abilitiesSize; ++i) {
        Ability* ability = abilityContainer->abilities.front();
        abilityContainer->abilities.pop_front();
        delete ability;
    }

    Json::Value abilitiesArray = object["abilities"];
    for (int i = 0; i < abilitiesArray.size(); ++i) {
        abilityContainer->abilities.push_back(
            abilityContainer->getAbilityFromString(
                abilitiesArray[i].asString()));
    }

    return abilityContainer;
}

void Deserializer::deserializeGameState(Json::Value object,
                                        GameState& gameState) {
    if (!object.isMember("version")) {
        throw std::runtime_error("Corrupted savefile: no version found.");
    }
    if (object["version"].asInt64() != CURRENT_SCHEMA_VERSION) {
        throw std::runtime_error("Corrupted savefile: version mismatch.");
    }
    if (!object.isMember("hash")) {
        throw std::runtime_error("Corrupted savefile: no hash found.");
    }
    if (!object.isMember("game")) {
        throw std::runtime_error("Corrupted savefile: no game data found.");
    }

    Json::Value game = object["game"];
    size_t checkHash = std::hash<std::string>()(game.toStyledString());

    if (object["hash"].asUInt64() != checkHash) {
        throw std::runtime_error("Corrupted savefile: hash mismatch.");
    }

    Json::Value players = game["players"];
    Json::Value userObject = players[0];
    Json::Value botObject = players[1];

    ShipContainer* userShipContainer =
        deserializeShipContainer(userObject["shipContainer"]);
    Field* userField =
        deserializeField(userObject["field"], *userShipContainer);
    PlayerParameters* userPlayerParameters =
        deserializePlayerParameters(userObject["playerParameters"]);
    AbilityContainer* userAbilityContainer =
        deserializeAbilityContainer(userObject["abilityContainer"]);

    ShipContainer* botShipContainer =
        deserializeShipContainer(botObject["shipContainer"]);
    Field* botField = deserializeField(botObject["field"], *botShipContainer);
    PlayerParameters* botPlayerParameters =
        deserializePlayerParameters(botObject["playerParameters"]);

    if (gameState.user != nullptr) {
        delete gameState.user;
    }

    if (gameState.bot != nullptr) {
        delete gameState.bot;
    }

    gameState.user = new Player(userField, userShipContainer,
                                userAbilityContainer, userPlayerParameters);
    gameState.bot =
        new Player(botField, botShipContainer, nullptr, botPlayerParameters);
    gameState.user->setEnemy(gameState.bot);
    gameState.bot->setEnemy(gameState.user);
}
