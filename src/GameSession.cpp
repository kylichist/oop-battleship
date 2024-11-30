#include "../include/GameSession.hpp"

#include "../include/RandomFieldProvider.hpp"

GameSession::GameSession() {
    gameState = new GameState();
    started = false;
    observers = std::vector<GameObserver*>();
}

GameSession::~GameSession() {
    if (gameState != nullptr) {
        delete gameState;
    }
}

void GameSession::start() {
    if (!getInitialized()) {
        throw std::runtime_error("GameSession is not initialized.");
    }
    started = true;
    for (auto observer : observers) {
        observer->onUserTurn(*gameState);
    }
}

void GameSession::initialize(uint8_t fieldRows, uint8_t fieldColumns,
                             std::map<uint8_t, uint8_t> shipLimits,
                             FieldProvider* userFieldProvider) {
    if (getStarted()) {
        throw std::runtime_error("Trying to initialize started GameSession.");
    }
    gameState->load(fieldRows, fieldColumns, shipLimits, userFieldProvider);
}

GameState& GameSession::getGameState() {
    return *gameState;
}

bool GameSession::getStarted() {
    return started;
}

bool GameSession::getInitialized() {
    return gameState->isInitialized();
}

void GameSession::restart() {
    gameState->resetBot();
}

void GameSession::botTurn() {
    Player& bot = gameState->getBot();
    Field& enemyField = bot.getEnemy().getField();
    RandomGenerator random = RandomGenerator();
    int16_t x = random.randomBetween(0, enemyField.getColumns() - 1);
    int16_t y = random.randomBetween(0, enemyField.getRows() - 1);
    Coordinates attackCoordinates = Coordinates(x, y);
    uint8_t damage = bot.getPlayerParameters().getDamage();
    enemyField.shootAt(attackCoordinates, damage);
}

void GameSession::makeAction(Action* action) {
    if (!getStarted()) {
        return;
    }
    if (!action->availability(*gameState)) {
        for (auto observer : observers) {
            observer->onActionDenied();
        }
        delete action;
        return;
    }

    ActionResult* result = action->execute(*gameState);
    for (auto observer : observers) {
        observer->onActionResult(result);
    }
    bool success = dynamic_cast<ActionResultFailure*>(result) == nullptr;
    if (success) {
        action->effect(*gameState);
    }

    if (success && action->getType() == ActionType::TERMINATING) {
        // проверка результатов хода и ход бота
        if (gameState->isFinished() && gameState->isUserWin()) {
            for (auto observer : observers) {
                observer->onUserWin();
            }
            restart();
        }

        for (auto observer : observers) {
            observer->onBotTurn();
        }
        botTurn();  // если нужно менять режим игры, см. сюда

        if (gameState->isFinished() && !gameState->isUserWin()) {
            // игра проиграна
            for (auto observer : observers) {
                observer->onBotWin();
            }
            started = false;
            delete gameState;
            gameState = new GameState();
        } else {
            onNewTurn();
        }
    }
    delete result;
    delete action;
}

void GameSession::onNewTurn() {
    gameState->getUser().getPlayerParameters().resetAll();
    for (auto observer : observers) {
        observer->onUserTurn(*gameState);
    }
}

void GameSession::addObserver(GameObserver* observer) {
    if (observer == nullptr) {
        return;
    }
    observers.push_back(observer);
}
