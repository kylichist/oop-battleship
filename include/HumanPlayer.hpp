#ifndef HUMANPLAYER_HPP  // HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "InputHandler.hpp"
#include "OutputHandler.hpp"
#include "Player.hpp"

class HumanPlayer : public Player {
private:
    InputHandler* inputHandler;
    OutputHandler* outputHandler;

public:
    HumanPlayer(uint8_t fieldRows, uint8_t fieldColumns,
                std::map<uint8_t, uint8_t> shipScheme,
                InputHandler* inputHandler, OutputHandler* outputHandler)
        : Player(fieldRows, fieldColumns, shipScheme),
          inputHandler(inputHandler),
          outputHandler(outputHandler) {}

    void makeTurn() override;
    ~HumanPlayer();
};

#endif  // HUMANPLAYER_HPP
