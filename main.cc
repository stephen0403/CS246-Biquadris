// #include <fstream>
#include "text.h"
#include "gameplay.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  std::string file1{"sequence1.txt"};
  std::string file2{"sequence2.txt"};
  int level = 0;
  unsigned int seed = 0;
  int currentPlayer = 0;                                        // current player
  
  std::unique_ptr<absBoard> board1 = std::make_unique<Board> (); // board1
  std::unique_ptr<absBoard> board2 = std::make_unique<Board> (); // board2
  std::vector<absBoard*> boards {board1.get(), board2.get()};
  std::vector<Level> levels{Level0(boards.at(currentPlayer)),
                            Level1(boards.at(currentPlayer)),
                            Level2(boards.at(currentPlayer)),
                            Level3(boards.at(currentPlayer)),
                            Level4(boards.at(currentPlayer))};

  for (int i = 1; i < argc; i += 2) {
    std::string arg{argv[i]};
    if (arg == "-text") {
      --i;
    } else {
      std::istringstream iss{argv[i + 1]};
      if (arg == "-startlevel") {
        iss >> level;
      } else if (arg == "-scriptfile1") {
        iss >> file1;
      } else if (arg == "-scriptfile2") {
        iss >> file2;
      } else if (arg == "-seed") {
        iss >> seed;
      }
    }  }

  //GamePlay game{file1, file2, 2, 2, seed};
  //TextDisplay td{&game};
  //std::string cmd;
  //td.display();
  std::cout << std::endl;
  while (std::cin >> cmd) {
    if (cmd == "d"/*rop"*/) {
      try {
        while(game.shift(0, 1, true));
      } catch (bool player) {
        std::cout << "Player " << player + 1 << " won!" << std::endl;
        return 0;
      }
    } else if (cmd == "c"/*lockwise"*/) {
      game.rotateBlock(1);
    } else if (cmd == "cc"/*ounterclockwise"*/) {
      game.rotateBlock(0);
    } else if (cmd == "r"/*ight"*/) {
      game.shift(1, 0);
    } else if (cmd == "l"/*eft"*/) {
      game.shift(-1, 0);
    } else if (cmd == "down") {
      game.shift(0, 1, false);
    } else if (cmd == "levelup") {
      game.levelUp();
    } else if (cmd == "leveldown") {
      game.levelDown();
    }
    if (cmd == "d" || cmd == "r" || cmd == "l" || cmd == "down" || cmd == "c" || cmd == "cc") {
      try {
        game.notify();
      } catch (int player) {
        std::cout << "Player " << player + 1 << " won!" << std::endl;
        return 0;
      }
    }
    if (cmd == "d") {
      game.switchPlayer();
    }
    td.display();
    std::cout << std::endl;
  }
}


