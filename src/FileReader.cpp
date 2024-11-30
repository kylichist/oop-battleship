#include "../include/FileReader.hpp"

void FileReader::readGameState(std::string path, GameState& gameState) {
    std::ifstream istream;
    istream.open(path);

    if (istream.fail()) {
        istream.close();
        throw std::runtime_error("File not found.");
    }

    istream >> gameState;
    istream.close();
}
