#ifndef GAMEINPUTCONTROLLER_HPP  // GAMEINPUTCONTROLLER_HPP
#define GAMEINPUTCONTROLLER_HPP

#include "Action.hpp"
#include "AttackAction.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "GameCommand.hpp"
#include "GameOutputController.hpp"
#include "GameSession.hpp"
#include "ManualFieldProvider.hpp"
#include "MoveAction.hpp"
#include "RandomFieldProvider.hpp"
#include "UseAbilityAction.hpp"

template <class Input, class Output>
class GameInputController {
private:
    GameSession& gameSession;
    Input& input;
    Output& output;

    void load() {
        std::string readPath =
            input.requestString("Enter savefile path (by default: save.json):");
        if (readPath.size() == 0) {
            readPath = "save.json";
        }

        FileReader reader = FileReader(readPath);
        reader.readGameState(gameSession.getGameState());
        output.printMessage("Savefile loaded.");
    }

    void save() {
        std::string loadPath =
            input.requestString("Enter savefile path (by default: save.json):");
        if (loadPath.size() == 0) {
            loadPath = "save.json";
        }

        FileWriter writer = FileWriter(loadPath);
        writer.writeGameState(gameSession.getGameState());
        output.printMessage("Savefile written.");
    }

public:
    GameInputController(GameSession& gameSession, Input& input, Output& output)
        : gameSession(gameSession), input(input), output(output) {}

    bool run() {
        GameCommand gameCommand = GameCommand::HELP;
        while (gameCommand != GameCommand::QUIT) {
            Action* action = nullptr;
            switch (gameCommand) {
                case GameCommand::MOVE_DOWN:
                    action = new MoveAction(0, 1);
                    break;
                case GameCommand::MOVE_UP:
                    action = new MoveAction(0, -1);
                    break;
                case GameCommand::MOVE_LEFT:
                    action = new MoveAction(-1, 0);
                    break;
                case GameCommand::MOVE_RIGHT:
                    action = new MoveAction(1, 0);
                    break;
                case GameCommand::LOAD:
                    try {
                        load();
                    } catch (std::runtime_error e) {
                        output.printError(e);
                    }
                    break;
                case GameCommand::SAVE:
                    try {
                        save();
                    } catch (std::runtime_error e) {
                        output.printError(e);
                    }
                    break;
                case GameCommand::ATTACK:
                    action = new AttackAction();
                    break;
                case GameCommand::USE_ABILITY:
                    action = new UseAbilityAction();
                    break;
                case GameCommand::HELP:
                    output.printMessage("Help:");
                    output.printMessage(input.getInfo());
                    break;
                default:
                    break;
            }
            if (action != nullptr) {
                gameSession.makeAction(action);
            }
            if (!gameSession.getStarted()) {
                break;
            }
            gameCommand = input.requestCommand();
        }

        return gameCommand == GameCommand::QUIT;
    }

    bool setup() {
        bool quit = false;
        while (true) {
            int option = input.requestInt(
                1, 3, "Select option:\n1. New game\n2. Load savefile\n3. Quit");
            if (option == 1) {
                int rows = input.requestInt(1, 100, "Select field rows:");
                int columns = input.requestInt(1, 100, "Select field columns:");
                int s1 = input.requestInt(1, 100,
                                          "Select count of ships length = 1:");
                int s2 = input.requestInt(0, 100,
                                          "Select count of ships length = 2:");
                int s3 = input.requestInt(0, 100,
                                          "Select count of ships length = 3:");
                int s4 = input.requestInt(0, 100,
                                          "Select count of ships length = 4:");
                std::map<uint8_t, uint8_t> limits = {
                    {1, s1}, {2, s2}, {3, s3}, {4, s4}};
                FieldProvider* fieldProvider;
                bool choice = input.requestChoice("Place ships randomly?");
                if (choice) {
                    fieldProvider = new RandomFieldProvider();
                } else {
                    fieldProvider =
                        new ManualFieldProvider<Input, Output>(input, output);
                }
                try {
                    gameSession.initialize(rows, columns, limits,
                                           fieldProvider);
                } catch (std::runtime_error e) {
                    delete fieldProvider;
                    output.printError(e);
                    continue;
                }
                gameSession.start();
                delete fieldProvider;
                break;
            }
            if (option == 2) {
                try {
                    load();
                } catch (std::runtime_error e) {
                    output.printError(e);
                    continue;
                }
                gameSession.start();
                break;
            }
            if (option == 3) {
                quit = true;
                break;
            }
        }

        return quit;
    }
};

#endif  // GAMEINPUTCONTROLLER_HPP
