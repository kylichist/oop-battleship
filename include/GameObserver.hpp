#ifndef GAMEOBSERVER_HPP  // GAMEOBSERVER_HPP
#define GAMEOBSERVER_HPP

#include "ActionResult.hpp"
#include "GameState.hpp"

class GameObserver {
public:
    virtual void onActionDenied() = 0;
    virtual void onActionResult(ActionResult* result) = 0;
    virtual void onUserTurn(GameState& gameState) = 0;
    virtual void onBotTurn() = 0;
    virtual void onBotWin() = 0;
    virtual void onUserWin() = 0;
};

#endif  // GAMEOBSERVER_HPP
