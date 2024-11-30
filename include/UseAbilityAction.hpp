#ifndef USEABILITYACTION_HPP  // USEABILITYACTION_HPP
#define USEABILITYACTION_HPP

#include "Action.hpp"

class UseAbilityAction : public Action {
public:
    ActionType getType() override;

    bool availability(GameState& gameState) override;

    ActionResult* execute(GameState& gameState) override;

    void effect(GameState& gameState) override;
};

#endif  // USEABILITYACTION_HPP
