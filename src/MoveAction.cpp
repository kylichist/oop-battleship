#include "../include/MoveAction.hpp"

ActionType MoveAction::getType() {
    return ActionType::MANY;
}

ActionResult* MoveAction::execute(GameState& gameState) {
    Player& user = gameState.getUser();
    Coordinates& coordinates = user.getSelectedCoordinates();
    coordinates.x += dx;
    coordinates.y += dy;
    return new ActionResultSuccess(
        "Moved to x: " + std::to_string(coordinates.x) +
        ", y: " + std::to_string(coordinates.y));
}
