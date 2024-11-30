#include "../include/UseAbilityAction.hpp"

ActionType UseAbilityAction::getType() {
    return ActionType::ONCE;
}

bool UseAbilityAction::availability(GameState& gameState) {
    return !gameState.getUser().getPlayerParameters().getIsAbilityUsed();
}

ActionResult* UseAbilityAction::execute(GameState& gameState) {
    AbilityResult* abilityResult;
    try {
        Player& user = gameState.getUser();
        abilityResult = user.getAbilityContainer().useAbility(user);
    } catch (std::runtime_error e) {
        return new ActionResultFailure(e);
    }
    ActionResult* result = new ActionResultSuccess(abilityResult->getResult());
    delete abilityResult;
    return result;
}

void UseAbilityAction::effect(GameState& gameState) {
    gameState.getUser().getPlayerParameters().setIsAbilityUsed(true);
}
