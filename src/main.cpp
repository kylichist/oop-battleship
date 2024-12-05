#include "../include/ConsoleInput.hpp"
#include "../include/ConsoleOutput.hpp"
#include "../include/FileReader.hpp"
#include "../include/GameInputController.hpp"
#include "../include/GameOutputController.hpp"
#include "../include/GameSession.hpp"

int main() {
    ConsoleInput consoleInput = ConsoleInput();
    ConsoleOutput consoleOutput = ConsoleOutput();

    try {
        Json::Value configObject = FileReader("config.json").readConfigFile();
        ControlConfiguration config =
            Deserializer().deserializeControlConfiguration(configObject);
        consoleInput.loadConfiguration(config);
        consoleOutput.printMessage("Loaded control config.");
    } catch (std::runtime_error e) {
        consoleOutput.printError(e);
    }

    GameSession gameSession = GameSession();

    GameOutputController<ConsoleOutput>* outputController =
        new GameOutputController<ConsoleOutput>(consoleOutput);
    gameSession.addObserver(outputController);

    GameInputController<ConsoleInput, ConsoleOutput> inputController =
        GameInputController<ConsoleInput, ConsoleOutput>(
            gameSession, consoleInput, consoleOutput);

    bool quit = inputController.setup();
    while (!quit) {
        quit = inputController.run();
        if (quit) {
            break;
        }
        quit = inputController.setup();
    }

    delete outputController;
    return 0;
}
