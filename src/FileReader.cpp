#include "../include/FileReader.hpp"

FileReader::FileReader(std::string path) : file(std::fopen(path.c_str(), "r")) {
    if (file == nullptr) {
        throw std::runtime_error("File not found.");
    }
}

char* FileReader::readToBuffer() {
    std::fseek(file, 0, SEEK_END);
    size_t size = std::ftell(file);

    char* buffer = new char[size + 1]{};

    std::rewind(file);
    std::fread(buffer, sizeof(char), size, file);

    return buffer;
}

void FileReader::readGameState(GameState& gameState) {
    char* buffer = readToBuffer();

    std::stringstream(buffer) >> gameState;

    delete[] buffer;
}

Json::Value FileReader::readConfigFile() {
    Json::Value object;
    char* buffer = readToBuffer();
    try {
        std::stringstream(buffer) >> object;
    } catch (Json::RuntimeError e) {
        delete[] buffer;
        throw std::runtime_error("Corrupted config file: malformed json.");
    } catch (Json::LogicError e) {
        delete[] buffer;
        throw std::runtime_error("Corrupted config file: malformed json.");
    }
    delete[] buffer;

    return object;
}

FileReader::~FileReader() {
    std::fclose(file);
}
