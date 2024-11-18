#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>

#include "../include/BotPlayer.hpp"
#include "../include/ConsoleInputHandler.hpp"
#include "../include/ConsoleOutputHandler.hpp"
#include "../include/Coordinates.hpp"
#include "../include/Field.hpp"
#include "../include/FieldProvider.hpp"
#include "../include/GameSession.hpp"
#include "../include/HumanPlayer.hpp"
#include "../include/RandomFieldProvider.hpp"
#include "../include/RandomGenerator.hpp"
#include "../include/Ship.hpp"
#include "../include/ShipContainer.hpp"

int main() {
    // параметры тестовой игры
    uint8_t rows = 10, columns = 10;
    std::map<uint8_t, uint8_t> limits = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};

    // игровые сущности
    Player* player1 =
        new HumanPlayer(rows, columns, limits, new ConsoleInputHandler(),
                        new ConsoleOutputHandler());
    Player* player2 = new BotPlayer(rows, columns, limits);
    // Player* player2 =
    //     new HumanPlayer(rows, columns, limits, new ConsoleInputHandler(),
    //                     new ConsoleOutputHandler());

    FieldProvider* fieldProvider = new RandomFieldProvider();
    fieldProvider->placeShips(player1->getField(), player1->getShipContainer());
    fieldProvider->placeShips(player2->getField(), player2->getShipContainer());
    delete fieldProvider;

    OutputHandler* keyWriter = new ConsoleOutputHandler();
    keyWriter->printMessage("Key:");
    keyWriter->printField(player2->getField(), false);
    delete keyWriter;

    GameSession gameSession = GameSession(player1, player2);

    gameSession.start();

    return 0;
}
