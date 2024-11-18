#include <stdexcept>

#include "../include/HumanPlayer.hpp"

void HumanPlayer::makeTurn() {
    outputHandler->printMessage("Your turn");
    outputHandler->printOnTurnStart(*this);
    bool finished = false;
    while (!finished) {
        outputHandler->printMessage("Select action:");
        Action action = inputHandler->getAction();
        if (action == Action::SELECT) {
            outputHandler->printMessage("Select coordinates:");
            selectedCoodrinates = inputHandler->getCoordinates();
            outputHandler->printMessage("Selected coordinates:");
            outputHandler->printCoordinates(selectedCoodrinates);
        } else if (action == Action::ATTACK) {
            outputHandler->printMessage("Confirm attack coordinates (y/n)");
            outputHandler->printCoordinates(selectedCoodrinates);
            bool confirmation = inputHandler->getChoice();
            if (!confirmation) {
                continue;
            }

            try {
                enemy->getField().shootAt(selectedCoodrinates,
                                          playerParameters->getDamage());
                playerParameters->resetAttackParameters();
                outputHandler->printMessage("Attacked at:");
                outputHandler->printCoordinates(selectedCoodrinates);
                finished = true;
            } catch (std::runtime_error e) {
                outputHandler->printMessage(e.what());
                continue;
            }
        } else if (action == Action::USE_ABILITY) {
            if (playerParameters->getIsAbilityUsed()) {
                outputHandler->printMessage(
                    "You have already used ability in this turn");
                continue;
            }
            if (abilityContainer->getAbilitiesCount() != 0) {
                outputHandler->printMessage(
                    "Confirm ability usage: " + abilityContainer->peek() +
                    " (y/n)");
                bool confirmation = inputHandler->getChoice();
                if (!confirmation) {
                    continue;
                }
            }

            try {
                AbilityResult* result = abilityContainer->useAbility();
                outputHandler->printMessage(result->getResult());
                delete result;
                outputHandler->printAbilitites(*abilityContainer);
                playerParameters->setIsAbilityUsed(true);
            } catch (std::runtime_error e) {
                outputHandler->printMessage(e.what());
                continue;
            }
        }
    }
    outputHandler->printMessage("Your turn has finished");
    resetSelectedCoordinates();
    resetIsAbilityUsed();
}

HumanPlayer::~HumanPlayer() {
    delete inputHandler;
    delete outputHandler;
}
