set(Battleship_LIB_SRC
    AbilityContainer.cpp
    BombardAbility.cpp
    BotPlayer.cpp
    ConsoleInputHandler.cpp
    ConsoleOutputHandler.cpp
    DoubleDamageAbility.cpp
    Field.cpp
    GameSession.cpp
    HumanPlayer.cpp
    OutputHandler.cpp
    Player.cpp
    PlayerParameters.cpp
    RandomGenerator.cpp
    ScannerAbility.cpp
    Ship.cpp
    ShipContainer.cpp
    RandomFieldProvider.cpp
)

set(Battleship_EXEC_SRC
    main.cpp
)

PREPEND(Battleship_LIB_SRC)
set(Battleship_LIB_SRC ${Battleship_LIB_SRC} PARENT_SCOPE)

PREPEND(Battleship_EXEC_SRC)
set(Battleship_EXEC_SRC ${Battleship_EXEC_SRC} PARENT_SCOPE)
