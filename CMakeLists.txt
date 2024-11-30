cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(Battleship
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

include_directories(include)
aux_source_directory(src Battleship_LIB_SRC)
string(REPLACE "src/main.cpp" "" Battleship_LIB_SRC "${Battleship_LIB_SRC}")
set(Battleship_EXEC_SRC src/main.cpp)

add_subdirectory(src)
add_subdirectory(include)

add_library(battleship STATIC ${Battleship_LIB_SRC})
add_executable(Battleship ${Battleship_EXEC_SRC})

find_package(jsoncpp REQUIRED)

target_link_libraries(Battleship PRIVATE battleship jsoncpp_lib)
