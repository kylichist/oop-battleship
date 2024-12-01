#include "../include/FileWriter.hpp"

FileWriter::FileWriter(std::string path) : file(std::fopen(path.c_str(), "w")) {
    if (file == nullptr) {
        throw std::runtime_error("Could not open file.");
    }
}

void FileWriter::writeGameState(GameState& gameState) {
    std::stringstream ss;
    ss << gameState;

    if (std::fputs(ss.str().c_str(), file) == EOF) {
        throw std::runtime_error("Could not write to file.");
    }
}

FileWriter::~FileWriter() {
    std::fclose(file);
}
