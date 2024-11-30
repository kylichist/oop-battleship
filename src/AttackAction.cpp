#include "../include/AttackAction.hpp"

ActionType AttackAction::getType() {
    return ActionType::TERMINATING;
}

ActionResult* AttackAction::execute(GameState& gameState) {
    Player& user = gameState.getUser();
    PlayerParameters& userPlayerParameters = user.getPlayerParameters();

    uint8_t damage = userPlayerParameters.getDamage();
    Coordinates coordinates = user.getSelectedCoordinates();
    try {
        user.getEnemy().getField().shootAt(coordinates, damage);
    } catch (std::runtime_error e) {
        return new ActionResultFailure(e);
    }
    userPlayerParameters.resetAttackParameters();
    return new ActionResultSuccess("Attack was made.");
}
