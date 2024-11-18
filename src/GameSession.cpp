#include "../include/GameSession.hpp"

GameSession::GameSession(Player* player1, Player* player2) {
    players = {player1, player2};
    player1->setEnemy(player2);
    player2->setEnemy(player1);
}

void GameSession::start() {
    // uint8_t turnCount = 10;
    ShipContainer& shipContainer1 = players[0]->getShipContainer();
    ShipContainer& shipContainer2 = players[1]->getShipContainer();
    while (shipContainer1.getAliveShipsCount() != 0 &&
           shipContainer2.getAliveShipsCount() != 0) {
        // if (turnCount > 10) {
        //     break;
        // }
        // turnCount += 1;
        for (uint8_t i = 0; i < players.size(); ++i) {
            players[i]->makeTurn();
        }
    }
}

GameSession::~GameSession() {
    for (uint8_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}
