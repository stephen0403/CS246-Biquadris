#include "text.h"
#include <iostream>
#include <sstream>
#include "level.h"
#include "absBoard.h"
#include "board.h"
#include "trie.h"
#include <cctype>
#include "graphics.h"
#include "window.h"

int main(int argc, char *argv[]) {
  std::string file1{"sequence1.txt"};
  std::string file2{"sequence2.txt"};
  unsigned int seed = 0;
  int currPlayer = 0;
  bool textOnly = false;
  int startingLevel = 0;
  std::vector<int> playerLevels{0, 0}; //the levels each player is on
  std::vector<int> starsCount{0, 0}; // how many turns they've played without clearing a row

  // TRIE INITIALIZATION
  std::unique_ptr<TrieNode> trie = std::make_unique<TrieNode>();
  trie->insert("left");
  trie->insert("right");
  trie->insert("down");
  trie->insert("clockwise");
  trie->insert("counterclockwise");
  trie->insert("drop");
  trie->insert("levelup");
  trie->insert("leveldown");
  trie->insert("norandom");
  trie->insert("random");
  trie->insert("sequence");
  trie->insert("restart");
  
  for (int i = 1; i < argc; i += 2) {
    std::string arg{argv[i]};
    if (arg == "-text") {
      --i;
      textOnly = true;
    } else {
      std::istringstream iss{argv[i + 1]};
      if (arg == "-startlevel") {
        iss >> startingLevel;
        playerLevels.at(0) = startingLevel;
        playerLevels.at(1) = startingLevel;
      } else if (arg == "-scriptfile1") {
        iss >> file1;
      } else if (arg == "-scriptfile2") {
        iss >> file2;
      } else if (arg == "-seed") {
        iss >> seed;
      }
    }
  }

  
  std::unique_ptr<Board> board1 = std::make_unique<Board> (); // board1
  std::unique_ptr<Board> board2 = std::make_unique<Board> (); // board2
  std::vector<absBoard*> boards {board1.get(), board2.get()};
  std::vector<Level*> levels;
  std::unique_ptr<Level0> l0 = std::make_unique<Level0> (boards.at(currPlayer), file1, file2, seed);
  std::unique_ptr<Level1> l1 = std::make_unique<Level1> (boards.at(currPlayer), seed);
  std::unique_ptr<Level2> l2 = std::make_unique<Level2> (boards.at(currPlayer), seed);
  std::unique_ptr<Level3> l3 = std::make_unique<Level3> (boards.at(currPlayer), false, seed);
  std::unique_ptr<Level4> l4 = std::make_unique<Level4> (boards.at(currPlayer), false, seed);
  levels.emplace_back(l0.get());
  levels.emplace_back(l1.get());
  levels.emplace_back(l2.get());
  levels.emplace_back(l3.get());
  levels.emplace_back(l4.get());
  std::unique_ptr<TextDisplay> textObserver = std::make_unique<TextDisplay>
                                                (board1.get(), board2.get());

  std::unique_ptr<Block> currentBlock1 = levels.at(playerLevels[0])->newBlock(0); 
  std::unique_ptr<Block> nextBlock1 = levels.at(playerLevels[0])->newBlock(0);
  std::unique_ptr<Block> currentBlock2 = levels.at(playerLevels[1])->newBlock(1); 
  std::unique_ptr<Block> nextBlock2 = levels.at(playerLevels[1])->newBlock(1);
  std::vector<Block*> blocksQueue1{currentBlock1.get(), nextBlock1.get()};
  std::vector<Block*> blocksQueue2{currentBlock2.get(), nextBlock2.get()};
  std::vector<std::vector<Block*>> queueOfBlockQueues{blocksQueue1, blocksQueue2};
  std::vector<std::vector<Block*>> activeBlocks{queueOfBlockQueues.at(0), queueOfBlockQueues.at(1)};

  boards.at(currPlayer)->shift(0, 0, queueOfBlockQueues.at(currPlayer).front(), false);

  std::string cmd;
  bool readFromFile = false;
  std::ifstream file;
  int rowsCleared = 0;
  bool blind = false;
  std::vector<int> scores{0, 0};
  int highScore = 0;
  std::unique_ptr<Graphics> graphicObserver;
  if (!textOnly) graphicObserver = std::make_unique<Graphics>(board1.get(), board2.get(), playerLevels, currPlayer, scores, queueOfBlockQueues.at(0), queueOfBlockQueues.at(1), blind);

  

  while (true) {
    int nextPlayer = (currPlayer + 1) % 2;

    if (playerLevels.at(currPlayer) == 4 && starsCount[currPlayer] % 5 == 0 && starsCount[currPlayer] != 0) {
      // spawn new * block and drop it
      std::unique_ptr<Block> starBlock = std::make_unique<StarBlock>(playerLevels.at(currPlayer));
      bool dropping = true;
        while (dropping) {
          dropping = boards.at(currPlayer)->shift(0, 1, starBlock.get(), true);
      }
      rowsCleared = boards.at(currPlayer)->clearRows(scores, currPlayer);
      starsCount[currPlayer] = 0;
    }

    
    int multiplier = 0;
    // check for special action
    bool whoisblind = nextPlayer % 2 == 0;
    boards.at(0)->shift(0, 0, queueOfBlockQueues.at(0).front());
    boards.at(1)->shift(0, 0, queueOfBlockQueues.at(1).front());

    if (rowsCleared >= 1) {
      // add to score
      scores.at(nextPlayer) += (rowsCleared + playerLevels.at(nextPlayer)) * (rowsCleared + playerLevels.at(nextPlayer));
      highScore = std::max(highScore, scores.at(nextPlayer));
      starsCount[nextPlayer] = 0;
    }

    if (blind) {
      if (whoisblind) {
        textObserver->display(queueOfBlockQueues.at(0), queueOfBlockQueues.at(1), playerLevels, scores, !whoisblind, whoisblind);
        if (!textOnly) graphicObserver->updateBoard(playerLevels, scores, blind);

      } else {
        textObserver->display(queueOfBlockQueues.at(0), queueOfBlockQueues.at(1), playerLevels, scores, whoisblind, !whoisblind);
        if (!textOnly) graphicObserver->updateBoard(playerLevels, scores, blind);
      }
      blind = false;
    } else {
      textObserver->display(queueOfBlockQueues.at(0), queueOfBlockQueues.at(1), playerLevels, scores, false, false);
      if (!textOnly) graphicObserver->updateBoard(playerLevels, scores, blind);
    }
    
    if (rowsCleared >= 2) {
        std::cout << "Choose a special action: blind, heavy, force " << std::endl;
        std::string s;
        std::cin >> s;
        // implement trie?
        if (s == "blind" || s == "Blind" || s == "BLIND" || s == "b" || s == "B") {
          boards.at(nextPlayer)->triggerBlind();
          boards.at(nextPlayer)->setBlindTrue();
          blind = true;
          
        }
        else if (s == "heavy" || s == "Heavy" || s == "HEAVY" || s == "h" || s == "H") {
          boards.at(currPlayer)->setHeavy(); // should be nextPlayer;
        }
        else if (s == "force" || s == "Force" || s == "FORCE" || s == "f" || s == "F") {
          char c;
          std::cin >> c;

          if (currPlayer == 0) {
            auto oldBlock = std::move(currentBlock1);
            currentBlock1 = blockGen(c, playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock1.get(), nextBlock1.get()};
          } else {
            auto oldBlock = std::move(currentBlock2);
            currentBlock2 = blockGen(c, playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock2.get(), nextBlock2.get()};
          }
        }
      }

      rowsCleared = 0;

    if (readFromFile) {
      if (!(file >> multiplier)) {
        file.clear();
        multiplier = 1;
      }
      file >> cmd;
      if (file.eof()) {
        readFromFile = false;
        file.close();
        continue;
      }
    } else {
      if(!(std::cin >> multiplier)) {
        std::cin.clear();
        multiplier = 1;
      }
      if (!(std::cin >> cmd)) break;
    }
    
    //trie implementation - needs testing
    /////////////////////////////////////////
    std::string cmdlower = cmd;
    for (char& c : cmdlower) {
        c = std::tolower(c); // Convert each character to lowercase
    }
    std::vector<std::string> possibleCommands = trie->find(cmdlower);
    if (possibleCommands.size() == 1) {
      cmd = possibleCommands.front();
    }
    /////////////////////////////////////////
    for (int i = 0; i < multiplier; ++i) {
      if (cmd == "left") {
        boards.at(currPlayer)->shift(-1, 0, queueOfBlockQueues.at(currPlayer).front());
        if (playerLevels.at(currPlayer) >= 3 && i < 1) { // && cnt == amt
          bool one = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          if (!one) {
            queueOfBlockQueues.at(currPlayer).at(0) = std::move(queueOfBlockQueues.at(currPlayer).at(1));
            std::unique_ptr<Block> newBlock = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = newBlock.get();
            currPlayer = (currPlayer + 1) % 2;
          }
        }
        if (boards.at(currPlayer)->isHeavy()) {
          bool one = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          bool two = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          if (!one || !two) {
            queueOfBlockQueues.at(currPlayer).at(0) = std::move(queueOfBlockQueues.at(currPlayer).at(1));
            std::unique_ptr<Block> newBlock = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = newBlock.get();
            currPlayer = (currPlayer + 1) % 2;
          }
        }
      } 
      else if (cmd == "right") {
        boards.at(currPlayer)->shift(1, 0, queueOfBlockQueues.at(currPlayer).front());
        if (playerLevels.at(currPlayer) >= 3 && i < 1) { // && cnt == amt
          bool one = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          if (!one) {
            queueOfBlockQueues.at(currPlayer).at(0) = std::move(queueOfBlockQueues.at(currPlayer).at(1));
            if (currPlayer) {
            nextBlock2 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = nextBlock2.get();
            } else {
            nextBlock1 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = nextBlock1.get();
            }
            currPlayer = (currPlayer + 1) % 2;
          }
        }
        if (boards.at(currPlayer)->isHeavy()) {
          bool one = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          bool two = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
          if (!one || !two) {
            queueOfBlockQueues.at(currPlayer).at(0) = std::move(queueOfBlockQueues.at(currPlayer).at(1));
            if (currPlayer) {
            nextBlock2 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = nextBlock2.get();
            } else {
            nextBlock1 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
            queueOfBlockQueues.at(currPlayer).at(1) = nextBlock1.get();
            }
            currPlayer = (currPlayer + 1) % 2;
          }
        }
      } 
      else if (cmd == "down") {
        boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front());
      } 
      else if (cmd == "clockwise") {
        boards.at(currPlayer)->rotateBlock(queueOfBlockQueues.at(currPlayer).front(), true);
      } 
      else if (cmd == "counterclockwise") {
        boards.at(currPlayer)->rotateBlock(queueOfBlockQueues.at(currPlayer).front(), false);
      } 
      else if (cmd == "drop") {
        int dropping = true;
        if (boards.at(currPlayer)->isBlind()) {
          boards.at(currPlayer)->setBlindFalse();
          blind = false;
        }
        while (dropping) {
          if (dropping == 5) {
            std::cout << "Player " << ((currPlayer+1) % 2) + 1 << " has won!!!"<< std::endl;
            return 0;
          }
          dropping = boards.at(currPlayer)->shift(0, 1, queueOfBlockQueues.at(currPlayer).front(), true);
        }

        
        rowsCleared = boards.at(currPlayer)->clearRows(scores, currPlayer); // clears rows and checks how many rows cleared

        // if (rowsCleared == 0) { // check if we cleared more than 0 rows, if not then add to stars count
        //   ++starsCount[currPlayer];
        // } else {
        //   starsCount[currPlayer] = 0;
        // }
        if (currPlayer) {
          currentBlock2 = std::move(nextBlock2);
          nextBlock2 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
          queueOfBlockQueues.at(currPlayer) = {currentBlock2.get(), nextBlock2.get()};
        } else {
          currentBlock1 = std::move(nextBlock1);
          nextBlock1 = levels.at(playerLevels[currPlayer])->newBlock(currPlayer);
          queueOfBlockQueues.at(currPlayer) = {currentBlock1.get(), nextBlock1.get()};
        }
        if (boards.at(currPlayer)->isBlind()) {
          boards.at(currPlayer)->triggerBlind();
          blind = false;
        }
        if (i == multiplier - 1) currPlayer = (currPlayer + 1) % 2; //don't change player if they do xdrop, x>1
        starsCount[currPlayer]++;
      } 
      else if (cmd == "levelup") {
        if (playerLevels.at(currPlayer) < 4) ++playerLevels.at(currPlayer);
      } 
      else if (cmd == "leveldown") {
        if (playerLevels.at(currPlayer) > 0) --playerLevels.at(currPlayer);
      } 
      else if (cmd == "norandom" && i < 1) {
        l3 = std::make_unique<Level3> (boards.at(currPlayer), false, seed);
        l4 = std::make_unique<Level4> (boards.at(currPlayer), false, seed);
        levels.at(3) = l3.get();
        levels.at(4) = l4.get();
      } 
      else if (cmd == "random" && i < 1) {
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

        l3 = std::make_unique<Level3> (boards.at(currPlayer), true, seed, fileName);
        l4 = std::make_unique<Level4> (boards.at(currPlayer), true, seed, fileName);
        levels.at(3) = l3.get();
        levels.at(4) = l4.get();
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
        if (cmd == "I") {
          if (currPlayer == 0) {
            auto oldBlock = std::move(currentBlock1);
            currentBlock1 = std::make_unique<IBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock1.get(), nextBlock1.get()};
          } else {
            auto oldBlock = std::move(currentBlock2);
            currentBlock2 = std::make_unique<IBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock2.get(), nextBlock2.get()};
          }
        } else if (cmd == "J") {
          if (currPlayer == 0) {
            auto oldBlock = std::move(currentBlock1);
            currentBlock1 = std::make_unique<JBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock1.get(), nextBlock1.get()};
          } else {
            auto oldBlock = std::move(currentBlock2);
            currentBlock2 = std::make_unique<JBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock2.get(), nextBlock2.get()};
          }
        } else {
          if (currPlayer == 0) {
            auto oldBlock = std::move(currentBlock1);
            currentBlock1 = std::make_unique<LBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock1.get(), nextBlock1.get()};
          } else {
            auto oldBlock = std::move(currentBlock2);
            currentBlock2 = std::make_unique<LBlock>(playerLevels.at(currPlayer));
            boards.at(currPlayer)->swapBlock(oldBlock.get(), currentBlock1.get());
            queueOfBlockQueues.at(currPlayer) = {currentBlock2.get(), nextBlock2.get()};
          }
        }
      } else if (cmd == "highscore" && i < 1) {
        std::cout << "High Score: " << highScore << std::endl;
      }
      else if (cmd == "restart" && i < 1) { // call board's restart method
        board1 = std::make_unique<Board> (); // board1
        board2 = std::make_unique<Board> (); // board2
        boards = {board1.get(), board2.get()};
        levels = {};
        l0 = std::make_unique<Level0> (boards.at(currPlayer), file1, file2, seed);
        l1 = std::make_unique<Level1> (boards.at(currPlayer), seed);
        l2 = std::make_unique<Level2> (boards.at(currPlayer), seed);
        l3 = std::make_unique<Level3> (boards.at(currPlayer), false, seed);
        l4 = std::make_unique<Level4> (boards.at(currPlayer), false, seed);
        levels.emplace_back(l0.get());
        levels.emplace_back(l1.get());
        levels.emplace_back(l2.get());
        levels.emplace_back(l3.get());
        levels.emplace_back(l4.get());
        textObserver = std::make_unique<TextDisplay>
                                                      (board1.get(), board2.get());
        currentBlock1 = levels.at(playerLevels[0])->newBlock(0); 
        nextBlock1 = levels.at(playerLevels[0])->newBlock(0);
        currentBlock2 = levels.at(playerLevels[1])->newBlock(1); 
        nextBlock2 = levels.at(playerLevels[1])->newBlock(1);
        blocksQueue1 = {currentBlock1.get(), nextBlock1.get()};
        blocksQueue2 = {currentBlock2.get(), nextBlock2.get()};
        queueOfBlockQueues = {blocksQueue1, blocksQueue2};

        currPlayer = 0;
        playerLevels = {0, 0};

        boards.at(currPlayer)->shift(0, 0, queueOfBlockQueues.at(currPlayer).front(), false);

        cmd = "";
        readFromFile = false;
        rowsCleared = 0;
      }
    }
  }
}
