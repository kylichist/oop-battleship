#ifndef GAMEOUTPUTCONTROLLER_HPP  // GAMEOUTPUTCONTROLLER_HPP
#define GAMEOUTPUTCONTROLLER_HPP

#include <iostream>

#include "GameObserver.hpp"

template <class Output>
class GameOutputController : public GameObserver {
private:
    Output& output;

public:
    GameOutputController(Output& output) : output(output) {}

    void onActionDenied() override {
        output.printMessage("Action usage denied.");
    }

    void onActionResult(ActionResult* result) override {
        output.printMessage(result->getResult());
    }

    void onUserTurn(GameState& gameState) override {
        Player& user = gameState.getUser();
        output.printMessage("Your turn.");
        output.printMessage("Your field:");
        output.printField(user.getField());
        output.printMessage("Enemy field:");
        output.printField(user.getEnemy().getField(), true);
        if (user.getAbilityContainer().getAbilitiesCount() != 0) {
            output.printMessage("Available ability: " +
                                user.getAbilityContainer().peek());
        }
    }

    void onBotTurn() override { output.printMessage("Bot turn."); }

    void onBotWin() override { output.printMessage("Bot won. Game finished."); }

    void onUserWin() override { output.printMessage("You won. Next round."); }
};

#endif  // GAMEOUTPUTCONTROLLER_HPP
