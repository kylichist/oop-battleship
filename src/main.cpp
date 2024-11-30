#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <map>
#include <memory>

#include "../include/Coordinates.hpp"
#include "../include/Field.hpp"
#include "../include/FieldProvider.hpp"
#include "../include/GameInputController.hpp"
#include "../include/GameOutputController.hpp"
#include "../include/GameSession.hpp"
#include "../include/RandomFieldProvider.hpp"
#include "../include/RandomGenerator.hpp"
#include "../include/Ship.hpp"
#include "../include/ShipContainer.hpp"

void newGame(GameSession& gameSession, GameInputController& input);
bool gameCycle(GameSession& gameSession, GameInputController& input);

void newGame(GameSession& gameSession, GameInputController& input) {
    char control;
    while (!gameSession.getInitialized()) {
        std::cout << "New game (n) or load (l) ?" << std::endl;

        std::cin >> control;

        if (control == 'l') {
            input.executeCommand(GameCommand::LOAD);
        } else if (control == 'n') {
            input.executeCommand(GameCommand::INITIALIZE_MANUAL);
        } else {
            std::cout << "Unknown key." << std::endl;
        }
    }
}

bool gameCycle(GameSession& gameSession, GameInputController& input) {
    char control;
    bool quit = false;
    while (!quit && gameSession.getStarted()) {
        std::cin >> control;
        if (control == 'q') {
            quit = true;
        } else if (control == 'w') {
            input.executeCommand(GameCommand::MOVE_UP);
        } else if (control == 'a') {
            input.executeCommand(GameCommand::MOVE_LEFT);
        } else if (control == 's') {
            input.executeCommand(GameCommand::MOVE_DOWN);
        } else if (control == 'd') {
            input.executeCommand(GameCommand::MOVE_RIGHT);
        } else if (control == 'z') {
            input.executeCommand(GameCommand::ATTACK);
        } else if (control == 'x') {
            input.executeCommand(GameCommand::USE_ABILITY);
        } else if (control == 'p') {
            input.executeCommand(GameCommand::SAVE);
        } else if (control == 'o') {
            input.executeCommand(GameCommand::LOAD);
        }
    }
    return quit;
}

int main() {
    GameSession gameSession = GameSession();
    GameOutputController* output = new GameOutputController();
    gameSession.addObserver(output);
    GameInputController input = GameInputController(gameSession, *output);

    std::cout << "w: Move up\na: Move left\ns: Move down\nd: Move right\nz: "
                 "Attack\nx: Use ability\np: Save\no: Load\n";

    bool quit = false;
    while (!quit) {
        newGame(gameSession, input);
        gameSession.start();
        quit = gameCycle(gameSession, input);
    }

    delete output;
    return 0;
}
