#ifndef NOABILITYAVAILABLEEXCEPTION_HPP  // NOABILITYAVAILABLEEXCEPTION_HPP
#define NOABILITYAVAILABLEEXCEPTION_HPP

#include <stdexcept>

class NoAbilityAvailableException : public std::runtime_error {
public:
    NoAbilityAvailableException()
        : std::runtime_error("No abilities available") {}
};

#endif  // NOABILITYAVAILABLEEXCEPTION_HPP
