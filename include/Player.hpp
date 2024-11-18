#ifndef PLAYER_HPP  // PLAYER_HPP
#define PLAYER_HPP

#include "AbilityContainer.hpp"
#include "Field.hpp"
#include "PlayerParameters.hpp"
#include "ShipContainer.hpp"

class AbilityContainer;

class Player {
protected:
    Field* field;
    ShipContainer* shipContainer;
    AbilityContainer* abilityContainer;
    Coordinates selectedCoodrinates;
    PlayerParameters* playerParameters;
    // std::vector<Player*> enemies; // ?
    Player* enemy;
    void resetSelectedCoordinates();  // ?
    void resetIsAbilityUsed();

public:
    Player(uint8_t fieldRows, uint8_t fieldColumns,
           std::map<uint8_t, uint8_t> shipScheme);
    Field& getField();
    ShipContainer& getShipContainer();
    Coordinates& getSelectedCoordinates();
    PlayerParameters& getPlayerParameters();
    // void addEnemies(Player* enemies...); // ?
    Player& getEnemy();
    AbilityContainer& getAbilityContainer();
    void setEnemy(Player* enemy);
    virtual void makeTurn() = 0;

    virtual ~Player();
};

#endif  // PLAYER_HPP
