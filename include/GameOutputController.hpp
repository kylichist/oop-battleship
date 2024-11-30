#ifndef GAMEOUTPUTCONTROLLER_HPP  // GAMEOUTPUTCONTROLLER_HPP
#define GAMEOUTPUTCONTROLLER_HPP

#include <iostream>

#include "GameObserver.hpp"

class GameOutputController : public GameObserver {
private:
    void printField(Field& field, bool isEnemy = false);

public:
    void printMessage(std::string message);
    void onActionDenied() override;
    void onActionResult(ActionResult* result) override;
    void onUserTurn(GameState& gameState) override;
    void onBotTurn() override;
    void onBotWin() override;
    void onUserWin() override;
};

#endif  // GAMEOUTPUTCONTROLLER_HPP
