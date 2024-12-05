#include "../include/RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {
    std::random_device randomDevice;
    generator = std::mt19937(randomDevice());
}

std::mt19937 RandomGenerator::getGenerator() {
    return generator;
}

int RandomGenerator::randomBetween(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    std::uniform_int_distribution<> distribution(a, b);
    return distribution(generator);
}

int64_t RandomGenerator::randomId() {
    std::uniform_int_distribution<long long> distribution(
        0, std::numeric_limits<std::int64_t>::max());
    return distribution(generator);
}
