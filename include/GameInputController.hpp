#ifndef GAMEINPUTCONTROLLER_HPP  // GAMEINPUTCONTROLLER_HPP
#define GAMEINPUTCONTROLLER_HPP

#include "GameCommand.hpp"
#include "GameOutputController.hpp"
#include "GameSession.hpp"

class GameInputController {
private:
    GameSession& gameSession;
    GameOutputController& output;

public:
    GameInputController(GameSession& gameSession, GameOutputController& output)
        : gameSession(gameSession), output(output) {}

    void executeCommand(GameCommand gameCommand);
};

#endif  // GAMEINPUTCONTROLLER_HPP
