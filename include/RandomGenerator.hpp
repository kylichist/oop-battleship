#ifndef RANDOMGENERATOR_HPP  // RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>

class RandomGenerator {
private:
    std::mt19937 generator;

public:
    RandomGenerator();
    std::mt19937 getGenerator();
    int randomBetween(int a, int b);
    int64_t randomId();
};

#endif  // RANDOMGENERATOR_HPP
