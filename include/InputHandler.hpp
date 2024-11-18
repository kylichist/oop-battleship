#ifndef INPUTHANDLER_HPP  // INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "Action.hpp"
#include "Coordinates.hpp"

class InputHandler {
public:
    virtual Action getAction() = 0;
    virtual Coordinates getCoordinates() = 0;
    virtual bool getChoice() = 0;

    virtual ~InputHandler() {}
};

#endif  // INPUTHANDLER_HPP
