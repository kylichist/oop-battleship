#ifndef FILEWRITER_HPP  // FILEWRITER_HPP
#define FILEWRITER_HPP

#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#include "GameState.hpp"

class FileWriter {
private:
    std::FILE* file;

public:
    FileWriter(std::string path);
    void writeGameState(GameState& gameState);
    ~FileWriter();
};
#endif  // FILEWRITER_HPP
