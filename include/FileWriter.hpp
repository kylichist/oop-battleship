#ifndef FILEWRITER_HPP  // FILEWRITER_HPP
#define FILEWRITER_HPP

#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#include "GameState.hpp"

class FileWriter {
public:
    void writeGameState(std::string path, GameState& gameState);
};
#endif  // FILEWRITER_HPP
