#ifndef GAMESESSION_HPP  // GAMESESSION_HPP
#define GAMESESSION_HPP

#include <vector>

#include "Player.hpp"

class GameSession {
private:
    std::vector<Player*> players;

public:
    GameSession(Player* player1, Player* player2);
    void start();
    ~GameSession();
};

#endif  // GAMESESSION_HPP
