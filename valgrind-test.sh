./build.sh
valgrind --leak-check=full --track-origins=yes -s ./bin/Battleship
