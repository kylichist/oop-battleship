#ifndef ACTION_HPP  // ACTION_HPP
#define ACTION_HPP

#include "ActionResult.hpp"
#include "GameState.hpp"

enum class ActionType { ONCE, MANY, TERMINATING };

class Action {
public:
    virtual ActionType getType() = 0;

    virtual bool availability(GameState& gameState) { return true; }

    virtual ActionResult* execute(GameState& gameState) = 0;

    virtual void effect(GameState& gameState) {}

    virtual ~Action() {}
};

#endif  // ACTION_HPP
