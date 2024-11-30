#ifndef SELECTACTION_HPP  // SELECTACTION_HPP
#define SELECTACTION_HPP

#include "Action.hpp"

class MoveAction : public Action {
private:
    int16_t dx;
    int16_t dy;

public:
    MoveAction(int16_t dx, int16_t dy) : dx(dx), dy(dy) {}

    ActionType getType() override;
    ActionResult* execute(GameState& gameState) override;
};

#endif  // SELECTACTION_HPP
