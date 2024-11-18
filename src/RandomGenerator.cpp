#include "../include/RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {
    std::random_device randomDevice;
    generator = std::mt19937(randomDevice());
}

std::mt19937 RandomGenerator::getGenerator() {
    return generator;
}

int RandomGenerator::randomBetween(int a, int b) {
    std::uniform_int_distribution<> distribution(a, b);
    return distribution(generator);
}
