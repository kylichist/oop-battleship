#include "../include/GameInputController.hpp"

#include "../include/AttackAction.hpp"
#include "../include/FileReader.hpp"  // todo: replace
#include "../include/FileWriter.hpp"
#include "../include/MoveAction.hpp"
#include "../include/RandomFieldProvider.hpp"  // todo replace
#include "../include/UseAbilityAction.hpp"

void GameInputController::executeCommand(GameCommand gameCommand) {
    if (gameCommand == GameCommand::MOVE_DOWN) {
        Action* action = new MoveAction(0, 1);
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::MOVE_UP) {
        Action* action = new MoveAction(0, -1);
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::MOVE_LEFT) {
        Action* action = new MoveAction(-1, 0);
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::MOVE_RIGHT) {
        Action* action = new MoveAction(1, 0);
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::LOAD) {
        try {
            FileReader reader = FileReader("save.json");
            reader.readGameState(gameSession.getGameState());
            output.printMessage("Savefile loaded.");
        } catch (std::runtime_error e) {
            output.printMessage(e.what());
        }
        return;
    }

    if (gameCommand == GameCommand::SAVE) {
        try {
            FileWriter writer = FileWriter("save.json");
            writer.writeGameState(gameSession.getGameState());
            output.printMessage("Savefile written.");
        } catch (std::exception e) {
            output.printMessage(e.what());
        }
        return;
    }
    if (gameCommand == GameCommand::ATTACK) {
        Action* action = new AttackAction();
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::USE_ABILITY) {
        Action* action = new UseAbilityAction();
        gameSession.makeAction(action);
        return;
    }
    if (gameCommand == GameCommand::INITIALIZE_MANUAL) {
        //uint8_t rows = 10, columns = 10;
        //std::map<uint8_t, uint8_t> limits = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
        uint8_t rows = 2, columns = 2;
        std::map<uint8_t, uint8_t> limits = {{1, 1}};
        FieldProvider* fp = new RandomFieldProvider();
        gameSession.initialize(rows, columns, limits, fp);
        delete fp;
    }
}
