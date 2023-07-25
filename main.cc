// #include <fstream>
#include "text.h"
#include "gameplay.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  std::string file1{"sequence1.txt"};
  std::string file2{"sequence2.txt"};
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
  std::unique_ptr<Observer> textObserver = std::make_unique<TextDisplay>
                                                (board1.get(), board2.get());
  std::vector<int> playerLevels{0, 0}; //the levels each player is on
  std::vector<Block> blocksQueue{}


  for (int i = 1; i < argc; i += 2) {
    std::string arg{argv[i]};
    if (arg == "-text") {
      --i;
    } else {
      std::istringstream iss{argv[i + 1]};
      if (arg == "-startlevel") {
        iss >> playerLevels[currentPlayer];
      } else if (arg == "-scriptfile1") {
        iss >> file1;
      } else if (arg == "-scriptfile2") {
        iss >> file2;
      } else if (arg == "-seed") {
        iss >> seed;
      }
    }
  }
  std::cout << std::endl;
/////////
  std::string cmd;
  while (std::cin >> cmd) {
    if (cmd == "left") {
      boards[currentPlayer]->shift(-1, 0);
    } else if (cmd == "right") {
    } else if (cmd == "down") {
    } else if (cmd == "clockwise") {
    } else if (cmd == "counterclockwise") {
    } else if (cmd == "drop") {
    } else if (cmd == "levelup") {
      if (playerLevels[currentPlayer] < 4) ++playerLevels[currentPlayer];
    } else if (cmd == "leveldown") {
      if (playerLevels[currentPlayer] > 0) --playerLevels[currentPlayer];
    } else if (cmd == "norandom") { //needs further attention
    } else if (cmd == "random") {
    } else if (cmd == "sequence") { //needs further attention
    } else if (cmd == "restart") {
    }
    /*
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
    */
  }
}


