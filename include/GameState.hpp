#ifndef GAMESTATE_HPP  // GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Deserializer.hpp"
#include "FieldProvider.hpp"
#include "Player.hpp"
#include "Serializer.hpp"

class Player;
class FieldProvider;

class GameState {
private:
    Player* user;
    Player* bot;
    friend class Serializer;
    friend class Deserializer;

public:
    GameState(Player* user = nullptr, Player* bot = nullptr);
    Player& getUser();
    Player& getBot();

    bool isInitialized();
    bool isFinished();
    bool isUserWin();
    void resetBot();

    void load(uint8_t fieldRows, uint8_t fieldColumns,
              std::map<uint8_t, uint8_t> shipLimits,
              FieldProvider* userFieldProvider);
    void load(Json::Value object);
    Json::Value save();

    ~GameState();
};

std::ostream& operator<<(std::ostream& os, GameState& gameState);
std::istream& operator>>(std::istream& is, GameState& gameState);

#endif  // GAMESTATE_HPP
