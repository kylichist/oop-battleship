#ifndef FILEREADER_HPP  // FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#include "GameState.hpp"

class FileReader {
public:
    void readGameState(std::string path, GameState& gameState);
};
#endif  // FILEREADER_HPP
