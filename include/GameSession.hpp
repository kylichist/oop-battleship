#ifndef GAMESESSION_HPP  // GAMESESSION_HPP
#define GAMESESSION_HPP

#include <vector>

#include "Action.hpp"
#include "FieldProvider.hpp"
#include "GameObserver.hpp"
#include "GameState.hpp"
#include "Player.hpp"

class GameSession {
private:
    std::vector<GameObserver*> observers;
    GameState* gameState;
    bool started;
    void restart();
    void botTurn();
    void onNewTurn();

public:
    GameSession();
    void initialize(uint8_t fieldRows, uint8_t fieldColumns,
                    std::map<uint8_t, uint8_t> shipLimits,
                    FieldProvider* fieldProvider);
    GameState& getGameState();

    void makeAction(Action* action);
    void start();

    bool getStarted();
    bool getInitialized();

    void addObserver(GameObserver* observer);

    ~GameSession();
};

#endif  // GAMESESSION_HPP
