#ifndef CONSOLEINPUTHANDLER_HPP  // CONSOLEINPUTHANDLER_HPP
#define CONSOLEINPUTHANDLER_HPP

#include "InputHandler.hpp"

class ConsoleInputHandler : public InputHandler {
public:
    ConsoleInputHandler() {}

    Action getAction() override;
    Coordinates getCoordinates() override;
    bool getChoice() override;
};

#endif  // CONSOLEINPUTHANDLER_HPP
