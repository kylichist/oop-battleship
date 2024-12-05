#ifndef GAMECOMMAND_HPP  // GAMECOMMAND_HPP
#define GAMECOMMAND_HPP

#include <string>

enum class GameCommand {
    MOVE_LEFT = 0,
    MOVE_RIGHT = 1,
    MOVE_UP = 2,
    MOVE_DOWN = 3,
    ATTACK = 4,
    USE_ABILITY = 5,
    LOAD = 6,
    SAVE = 7,
    QUIT = 8,
    HELP = 9
};

static std::string commandToString(GameCommand command) {
    {
        switch (command) {
            case GameCommand::MOVE_UP:
                return "Move up";
                break;
            case GameCommand::MOVE_LEFT:
                return "Move left";
                break;
            case GameCommand::MOVE_DOWN:
                return "Move down";
                break;
            case GameCommand::MOVE_RIGHT:
                return "Move right";
                break;
            case GameCommand::ATTACK:
                return "Attack";
                break;
            case GameCommand::USE_ABILITY:
                return "Use ability";
                break;
            case GameCommand::LOAD:
                return "Load";
                break;
            case GameCommand::SAVE:
                return "Save";
                break;
            case GameCommand::QUIT:
                return "Quit";
                break;
            case GameCommand::HELP:
                return "Help";
                break;
            default:
                return "Unknown command";
                break;
        }
    }
}

#endif  // GAMECOMMAND_HPP
