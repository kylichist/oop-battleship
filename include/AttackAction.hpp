#ifndef ATTACKACTION_HPP  // ATTACKACTION_HPP
#define ATTACKACTION_HPP

#include "Action.hpp"
#include "Coordinates.hpp"

class AttackAction : public Action {
public:
    ActionType getType() override;
    ActionResult* execute(GameState& gameState) override;
};

#endif  // ATTACKACTION_HPP
