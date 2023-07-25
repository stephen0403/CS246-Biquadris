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
  std::vector<int> playerLevels{0, 0}; //the levels each player is on

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

  std::unique_ptr<absBoard> board1 = std::make_unique<Board> (); // board1
  std::unique_ptr<absBoard> board2 = std::make_unique<Board> (); // board2
  std::vector<absBoard*> boards {board1.get(), board2.get()};
  std::vector<Level> levels{Level0(boards.at(currentPlayer), file1, file2),
                            Level1(boards.at(currentPlayer)),
                            Level2(boards.at(currentPlayer)),
                            Level3(boards.at(currentPlayer)),
                            Level4(boards.at(currentPlayer))};
  std::unique_ptr<Observer> textObserver = std::make_unique<TextDisplay>
                                                (board1.get(), board2.get());
  std::unique_ptr<Block> currentBlock = levels[playerLevels[currentPlayer]].newBlock(); 
  std::unique_ptr<Block> nextBlock = levels[playerLevels[currentPlayer]].newBlock();
  std::vector<Block*> blocksQueue{currentBlock.get(), nextBlock.get()};

  std::cout << std::endl;

  std::string cmd;
  while (std::cin >> cmd) {
    bool dropped = false;

    if (cmd == "left") {
      dropped = boards[currentPlayer]->shift(-1, 0, blocksQueue.front());
    } else if (cmd == "right") {
      dropped = boards[currentPlayer]->shift(1, 0, blocksQueue.front());
    } else if (cmd == "down") {
      dropped = boards[currentPlayer]->shift(0, -1, blocksQueue.front());
    } else if (cmd == "clockwise") {
      boards[currentPlayer]->rotateBlock(blocksQueue.front(), true);
    } else if (cmd == "counterclockwise") {
      boards[currentPlayer]->rotateBlock(blocksQueue.front(), false);
    } else if (cmd == "drop") {
      dropped = boards[currentPlayer]->shift(0, -1, blocksQueue.front(), true);
    } else if (cmd == "levelup") {
      if (playerLevels[currentPlayer] < 4) ++playerLevels[currentPlayer];
    } else if (cmd == "leveldown") {
      if (playerLevels[currentPlayer] > 0) --playerLevels[currentPlayer];
    } else if (cmd == "norandom") {
      std::string fileName;
      std::cin >> fileName;
      levels.at(3) = Level3(boards.at(currentPlayer)/*, true, fileName*/);
      levels.at(4) = Level4(boards.at(currentPlayer)/*, true, fileName*/);
    } else if (cmd == "random") {
      levels.at(3) = Level3(boards.at(currentPlayer)/*, false*/);
      levels.at(4) = Level4(boards.at(currentPlayer)/*, false*/);
    } else if (cmd == "sequence") { //needs further attention
    } else if (cmd == "restart") {
    }

    if (dropped) {
        int rowsCleared = boards[currentPlayer]->clearRows();
        if (rowsCleared >= 2) {
          // call special action
        }
        currentPlayer = (currentPlayer + 1) % 2;

        // Questionable Codeblock
        // currentBlock = std::move(nextBlock);
        // nextBlock = levels[playerLevels[currentPlayer]].newBlock();
        // blocksQueue = {currentBlock.get(), nextBlock.get()};
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


