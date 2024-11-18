#ifndef BOTPLAYER_HPP  // BOTPLAYER_HPP
#define BOTPLAYER_HPP

#include "Player.hpp"

class BotPlayer : public Player {
public:
    BotPlayer(uint8_t fieldRows, uint8_t fieldColumns,
              std::map<uint8_t, uint8_t> shipScheme)
        : Player(fieldRows, fieldColumns, shipScheme) {}

    void makeTurn() override;
};

#endif  // BOTPLAYER_HPP
