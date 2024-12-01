#include "../include/FileReader.hpp"

FileReader::FileReader(std::string path) : file(std::fopen(path.c_str(), "r")) {
    if (file == nullptr) {
        throw std::runtime_error("File not found.");
    }
}

void FileReader::readGameState(GameState& gameState) {
    std::fseek(file, 0, SEEK_END);
    size_t size = std::ftell(file);

    char* buffer = new char[size];

    std::rewind(file);
    std::fread(buffer, sizeof(char), size, file);

    std::stringstream(buffer) >> gameState;

    delete[] buffer;
}

FileReader::~FileReader() {
    std::fclose(file);
}
