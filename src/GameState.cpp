#include "../include/GameState.hpp"
#include <iostream>

#include "../include/RandomFieldProvider.hpp"
#include "../include/Serializer.hpp"

GameState::GameState(Player* user, Player* bot) : user(user), bot(bot) {}

Player& GameState::getUser() {
    if (user == nullptr) {
        throw std::runtime_error(
            "Trying to access user from (probably) not initialized GameState.");
    }
    return *user;
}

Player& GameState::getBot() {
    if (bot == nullptr) {
        throw std::runtime_error(
            "Trying to access bot from (probably) not initialized GameState.");
    }
    return *bot;
}

bool GameState::isInitialized() {
    return user != nullptr && bot != nullptr;
}

bool GameState::isFinished() {
    if (!isInitialized()) {
        throw std::runtime_error(
            "Trying to access properties of (probably) not initialized "
            "GameState.");
    }
    return user->getShipContainer().getAliveShipsCount() == 0 ||
           bot->getShipContainer().getAliveShipsCount() == 0;
}

bool GameState::isUserWin() {
    if (!isInitialized()) {
        throw std::runtime_error(
            "Trying to access properties of (probably) not initialized "
            "GameState.");
    }
    return bot->getShipContainer().getAliveShipsCount() == 0;
}

void GameState::resetBot() {
    if (user == nullptr) {
        throw std::runtime_error(
            "Cannot reset bot player due to null user player.");
    }

    if (bot != nullptr) {
        delete bot;
    }

    uint8_t fieldRows = user->getField().getRows();
    uint8_t fieldColumns = user->getField().getColumns();
    std::map<uint8_t, uint8_t> shipLimits =
        user->getShipContainer().getLimits();

    Field* botField = new Field(fieldRows, fieldColumns);
    ShipContainer* botShipContainer = new ShipContainer(shipLimits);
    PlayerParameters* botPlayerParameters = new PlayerParameters();
    bot = new Player(botField, botShipContainer, nullptr, botPlayerParameters);

    FieldProvider* botFieldProvider = new RandomFieldProvider();
    botFieldProvider->placeShips(*botField, *botShipContainer);

    user->setEnemy(bot);
    bot->setEnemy(user);

    delete botFieldProvider;
}

GameState::~GameState() {
    if (user != nullptr) {
        delete user;
    }
    if (bot != nullptr) {
        delete bot;
    }
}

void GameState::load(uint8_t fieldRows, uint8_t fieldColumns,
                     std::map<uint8_t, uint8_t> shipLimits,
                     FieldProvider* userFieldProvider) {
    if (userFieldProvider == nullptr) {
        throw std::runtime_error("No FieldProvider provided.");
    }

    if (user != nullptr) {
        delete user;
    }

    Field* userField = new Field(fieldRows, fieldColumns);
    ShipContainer* userShipContainer = new ShipContainer(shipLimits);
    try {
        userFieldProvider->placeShips(*userField, *userShipContainer);
    } catch (std::runtime_error e) {
        delete userField;
        delete userShipContainer;
        throw e;
    }
    AbilityContainer* userAbilityContainer = new AbilityContainer();
    PlayerParameters* userPlayerParameters = new PlayerParameters();

    user = new Player(userField, userShipContainer, userAbilityContainer,
                      userPlayerParameters);

    resetBot();
}

void GameState::load(Json::Value object) {
    try {
        Deserializer().deserializeGameState(object, *this);
    } catch (Json::LogicError e) {
        throw std::runtime_error("Corrupted savefile: malformed json.");
    }
}

Json::Value GameState::save() {
    return Serializer().serializeGameState(this);
}

std::ostream& operator<<(std::ostream& os, GameState& gameState) {
    os << gameState.save();
    return os;
}

std::istream& operator>>(std::istream& is, GameState& gameState) {
    Json::Value object;
    try {
        is >> object;
    } catch (Json::RuntimeError e) {
        throw std::runtime_error("Corrupted savefile: malformed json.");
    }
    gameState.load(object);
    return is;
}
