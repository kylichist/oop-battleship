#include "../include/FileWriter.hpp"

void FileWriter::writeGameState(std::string path, GameState& gameState) {
    std::ofstream ostream;
    ostream.open(path);

    if (ostream.fail()) {
        ostream.close();
        throw std::runtime_error("Could not open savefile.");
    }

    ostream << gameState;
    ostream.close();
}
