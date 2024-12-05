#ifndef FILEREADER_HPP  // FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#include "GameState.hpp"

class FileReader {
private:
    std::FILE* file;
    char* readToBuffer();

public:
    FileReader(std::string path);
    void readGameState(GameState& gameState);
    Json::Value readConfigFile();
    ~FileReader();
};
#endif  // FILEREADER_HPP
