#include "text.h"
#include <iostream>
#include <sstream>
#include "level.h"

int main(int argc, char *argv[]) {
  std::string file1{"sequence1.txt"};
  std::string file2{"sequence2.txt"};
  unsigned int seed = 0;
  int currPlayer = 0;               // current player
  std::vector<int> playerLevels{0, 0}; //the levels each player is on

  for (int i = 1; i < argc; i += 2) {
    std::string arg{argv[i]};
    if (arg == "-text") {
      --i;
    } else {
      std::istringstream iss{argv[i + 1]};
      if (arg == "-startlevel") {
        iss >> playerLevels[currPlayer];
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
  std::vector<Level> levels{Level0(boards.at(currPlayer), file1, file2),
                            Level1(boards.at(currPlayer)),
                            Level2(boards.at(currPlayer)),
                            Level3(boards.at(currPlayer), false),
                            Level4(boards.at(currPlayer), false)};
  std::unique_ptr<Observer> textObserver = std::make_unique<TextDisplay>
                                                (board1.get(), board2.get());
  std::unique_ptr<Block> currentBlock = levels[playerLevels[currPlayer]].newBlock(currPlayer); 
  std::unique_ptr<Block> nextBlock = levels[playerLevels[currPlayer]].newBlock(currPlayer);
  std::vector<Block*> blocksQueue{currentBlock.get(), nextBlock.get()};

  std::cout << std::endl;

  std::string cmd;
  bool readFromFile = false;
  std::ifstream file;

  while (true) {

    if (readFromFile) {
      file >> cmd;
      if (file.eof()) {
        readFromFile = false;
        file.close();
        continue;
      }
    } else {
      if (!(std::cin >> cmd)) break;
    }

    bool dropped = false;
    if (cmd == "left") {
      dropped = boards.at(currPlayer)->shift(-1, 0, blocksQueue.front());
    } 
    else if (cmd == "right") {
      dropped = boards.at(currPlayer)->shift(1, 0, blocksQueue.front());
    } 
    else if (cmd == "down") {
      dropped = boards.at(currPlayer)->shift(0, -1, blocksQueue.front());
    } 
    else if (cmd == "clockwise") {
      boards.at(currPlayer)->rotateBlock(blocksQueue.front(), true);
    } 
    else if (cmd == "counterclockwise") {
      boards.at(currPlayer)->rotateBlock(blocksQueue.front(), false);
    } 
    else if (cmd == "drop") {
      dropped = boards.at(currPlayer)->shift(0, -1, blocksQueue.front(), true);
    } 
    else if (cmd == "levelup") {
      if (playerLevels[currPlayer] < 4) ++playerLevels[currPlayer];
    } 
    else if (cmd == "leveldown") {
      if (playerLevels[currPlayer] > 0) --playerLevels[currPlayer];
    } 
    else if (cmd == "norandom") {
      levels.at(3) = Level3(boards.at(currPlayer), false);
      levels.at(4) = Level4(boards.at(currPlayer), false);
    } 
    else if (cmd == "random") {
      std::string fileName;
      if (readFromFile) {
        file >> fileName;
        if (file.eof()) {
          readFromFile = false;
          file.close();
          std::cin >> fileName;
        }
      } else {
        std::cin >> fileName;
      }

      levels.at(3) = Level3(boards.at(currPlayer), true, fileName);
      levels.at(4) = Level4(boards.at(currPlayer), true, fileName);
    } 
    else if (cmd == "sequence") { //needs further attention
      std::string fileName;
      if (readFromFile) {
        file >> fileName;
        if (file.eof()) {
          readFromFile = false;
          file.close();
          std::cin >> fileName;
        }
      } else {
        std::cin >> fileName;
      }

      file = std::ifstream{fileName};
      readFromFile = true;
    } 
    else if (cmd == "I" || cmd == "J" || cmd == "L") { //changes the current block to these
      if (cmd == "I") blocksQueue.front() = std::make_unique<IBlock>().get();
      else if (cmd == "J") blocksQueue.front() = std::make_unique<JBlock>().get();
      else blocksQueue.front() = std::make_unique<LBlock>().get();
    } 
    else if (cmd == "restart") { // call board's restart method
    }

    if (dropped) {
      int rowsCleared = boards.at(currPlayer)->clearRows();

      currPlayer = (currPlayer + 1) % 2;
      currentBlock = std::move(nextBlock);
      nextBlock = levels[playerLevels[currPlayer]].newBlock(currPlayer);
      blocksQueue = {currentBlock.get(), nextBlock.get()};

      if (rowsCleared > 1) {
        // call special action

        std::string action;
        std::cout << "Enter a special action (blind, heavy, or force): " << std::endl;
        std::cin >> action;
        while (action != "blind" && action != "heavy" && action != "force") {
          std::cout << "Invalid action. Please enter a valid action (blind, heavy, or force): " << std::endl;
          std::cin >> action;
        }

        if (action == "blind") {
          // call blind
          // levels[playerLevels[currPlayer]].blind();
        }
        else if (action == "heavy") {
          // set currentBlock to heavy that falls by 2 rows

        }
        else {
          // call force
          std::string blockType;
          std::cout << "Enter a block type (I, J, L, O, S, Z, or T): " << std::endl;
          std::cin >> blockType;

          // set current block to generated Block of blockType
        }
      }

    }
  }
}


