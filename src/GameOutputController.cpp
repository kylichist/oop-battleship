#include <cmath>
#include <iomanip>

#include "../include/GameOutputController.hpp"

void GameOutputController::printField(Field& field, bool isEnemy) {
    uint8_t rowsWidth = int(std::log10(field.getRows()) + 1);
    uint8_t columnsWidth = int(std::log10(field.getColumns()) + 1);

    std::cout << std::setw(columnsWidth) << " ";
    for (uint8_t i = 0; i < field.getColumns(); ++i) {
        std::cout << " " << std::internal << std::setw(columnsWidth) << +i;
    }
    std::cout << std::endl;
    for (uint8_t y = 0; y < field.getRows(); ++y) {
        std::cout << std::right << std::setw(rowsWidth) << +y;
        for (uint8_t x = 0; x < field.getColumns(); ++x) {
            Tile tile = field.getTile(x, y);
            std::cout << " " << std::internal << std::setw(columnsWidth);
            bool hidden = tile.tileState == TileState::HIDDEN;
            bool hasShip = tile.ship != nullptr;
            if (hidden && isEnemy) {
                std::cout << "H";
            }
            if (hidden && !isEnemy && !hasShip) {
                std::cout << "~";
            }
            if (hasShip && ((hidden && !isEnemy) || (!hidden))) {
                std::cout << static_cast<int>(
                    tile.ship->getSegment(field.getSegmentIndex(x, y)));
            }
            if (!hidden && !hasShip) {
                std::cout << "X";
            }
        }
        std::cout << std::endl;
    }
}

void GameOutputController::onActionDenied() {
    std::cout << "Action usage denied" << std::endl;
}

void GameOutputController::onActionResult(ActionResult* result) {
    std::cout << result->getResult() << std::endl;
}

void GameOutputController::onUserTurn(GameState& gameState) {
    Player& user = gameState.getUser();
    std::cout << "Your turn." << std::endl;
    std::cout << "Your field:" << std::endl;
    printField(user.getField());
    std::cout << "Enemy field:" << std::endl;
    printField(user.getEnemy().getField(), true);
    if (user.getAbilityContainer().getAbilitiesCount() != 0) {
        std::cout << "Available ability: " << user.getAbilityContainer().peek()
                  << std::endl;
    }
}

void GameOutputController::onBotTurn() {
    std::cout << "Bot turn." << std::endl;
}

void GameOutputController::onBotWin() {
    std::cout << "Bot won. Game finished." << std::endl;
}

void GameOutputController::onUserWin() {
    std::cout << "You won. Next round." << std::endl;
}

void GameOutputController::printMessage(std::string message) {
    std::cout << message << std::endl;
}
