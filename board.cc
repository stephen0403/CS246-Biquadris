#include "board.h"
#include "block.h"
// #include <sstream>

// board is ptr to absBoard
// theBoard is the vec vec char board


Board::Board(): numRows{18}, numCols{11}, theBoard(numRows, std::vector<Cell>(numCols, Cell{})) {}

char Board::tileAt(int row, int col) { return theBoard.at(row).at(col); }

Board::~Board() {}

void Board::render() {
  notifyObservers();
}

bool Board::isHeavy() {
  return heavy;
}

void Board::setHeavy() {
  heavy = true;
}


char Board::getState(int row, int col) const {
  return board->tileAt(row, col);
}

static bool isFull(const std::vector<char> &row) {
  for (auto c : row) {
    if (c == ' ') {
      return false;
    }
  }
  return true;
}

bool Board::shift(int x, int y, Block *block, bool drop) {
  // auto block = queue.front().get();
  std::vector<std::vector<int>> &pos = block->pos;
  for (int i = 0; i < 4; ++i) {
    theBoard.at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    if (pos[i][0] + y >= numRows || pos[i][1] + x < 0 || pos[i][1] + x >= numCols ||
        theBoard.at(pos[i][0] + y).at(pos[i][1] + x) != ' ') {
      if (y && drop) {
        for (int i = 0; i < 4; ++i) {
          if (block->pos[i][0] < 3) {
            for (int i = 0; i < 4; ++i) {
              block->pos[i][0] += y;
              block->pos[i][1] += x;
              theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
            }
            throw; // winner
          }
        }
      }
      for (int i = 0; i < 4; ++i) {
        theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
      }
      return false;
    }
  }
  block->lowerLeft[0] += y;
  block->lowerLeft[1] += x;
  for (int i = 0; i < 4; ++i) {
    block->pos[i][0] += y;
    block->pos[i][1] += x;
    theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
  }
  return true;
}

bool Board::swapBlock(Block *oldBlock, Block *newBlock) {
  std::vector<std::vector<int>> &oldBlockPos = oldBlock->pos;
  std::vector<std::vector<int>> &newBlockPos = newBlock->pos;
  char oldBlockType = oldBlock->getType();
  char newBlockType = newBlock->getType();

  for (int i = 0; i < 4; ++i) {
    theBoard.at(oldBlockPos[i][0]).at(oldBlockPos[i][1]) = ' ';
  }
  // for (int i = 0; i < 4; ++i) {
  //   if (theBoard.at(newBlockPos[i][0]).at(newBlockPos[i][1]) != ' ') {
  //     for (int j = 0; j < 4; ++i) {
  //       theBoard.at(oldBlockPos[j][0]).at(oldBlockPos[j][1]) = oldBlockType;
  //     }
  //     return false;
  //   }
  // }
  // for (int i = 0; i < 4; ++i) {
  //   theBoard.at(newBlockPos[i][0]).at(newBlockPos[i][1]) = newBlockType;
  // }
  return true;
}

// bool Board::clearRows() {
//   std::vector<std::vector<char>> newBoard(18, std::vector<char>(11, ' '));
//   int cur_row = 17;
//   bool cleared = false;
//   for (int i = 17; i >= 3; --i) {
//     if (!isFull(theBoard.at(i))) {
//       newBoard.at(cur_row) = theBoard.at(i);
//       --cur_row;
//     } else {
//       cleared = true;
//     }
//   }
//   theBoard = newBoard;
//   return cleared;
// }

int Board::clearRows() {
  int rowsCleared = 0;
  for (int i = numRows - 1; i >= 0; i--) {
    if (isFull(theBoard.at(i))) {
      rowsCleared++;
      for (int j = i; j > 0; j--) {
        theBoard.at(j) = theBoard.at(j - 1);
      }
      i++;
    }
  }
  return rowsCleared;
}

void Board::rotateBlock(Block *block, bool clockwise) {
  // auto block = queue.front().get();
  std::vector<std::vector<int>> &pos = block->pos;
  int dest[4][2];
  if (clockwise) {
    for (int i = 0; i < 4; ++i) {
      dest[i][0] = pos[i][1];
      dest[i][1] = -pos[i][0];
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      dest[i][0] = -pos[i][1];
      dest[i][1] = pos[i][0];
    }
  }
  int newLowerLeft[2] = {dest[0][0], dest[0][1]};
  for (int i = 0; i < 4; ++i) {
    if (dest[i][0] > newLowerLeft[0]) {
      newLowerLeft[0] = dest[i][0];
    }
    if (dest[i][1] < newLowerLeft[1]) {
      newLowerLeft[1] = dest[i][1];
    }
  }
  for (int i = 0; i < 4; ++i) {
    theBoard.at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    dest[i][0] += block->lowerLeft[0] - newLowerLeft[0];
    dest[i][1] += block->lowerLeft[1] - newLowerLeft[1];
    if (dest[i][1] >= numCols || theBoard.at(dest[i][0]).at(dest[i][1]) != ' ') {
      for (int i = 0; i < 4; ++i) {
        theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
      }
      return;
    }
  }
  for (int i = 0; i < 4; ++i) {
    block->pos[i][0] = dest[i][0];
    block->pos[i][1] = dest[i][1];
    theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
  }
}

void Board::putBlock(int col, char type) {
  for (int i = 3; i < 18; ++i) {
    if (theBoard.at(i).at(5) != ' ') {
      if (i > 3) {
        theBoard.at(i - 1).at(col) = type;
        return;
      } else {
        throw; // throw what? Orginally curplayer
      }
    }
  }
}

// std::string Board::getScore() const {
//   std::ostringstream res;
//   res << " Score:";
//   int numSpaces = 5 - numDigits(score);
//   while (numSpaces) {
//     res << " ";
//     --numSpaces;
//   }
//   res << score;
//   return res.str();
// }

void Board::triggerBlind() {
  blindActivated = !blindActivated;
}

bool Board::isBlind() {
  return blindActivated;
}



// void Board::move(int x, int y) {
//   current->updatePos(x, y);
// }

// void Board::rotate(bool clockwise) {
//   current->rotate(clockwise);
//   current->updatePos(0, 0);
// }

// void Board::updateCurrent() {
//   current = next;
// }



// void Board::updateScore() {
//   for (auto &row : board) {
//     if (isFull(row)) {
//       ++score;
//     }
//   }
//   score += level;
// }

/////////////// new clearRows() ////////////////////////////

/*
bool GamePlay::clearRows() {
  std::vector<std::vector<Cell>> newBoard(18, std::vector<Cell>(11, Cell{}));
  int cur_row = 17;
  int rowsCleared = 0;
  for (int i = 17; i >= 0; --i) {
    if (!isFull(boards[curPlayer].board.at(i))) {
      newBoard.at(cur_row) = boards[curPlayer].board.at(i);
      --cur_row;
    } else {
      ++rowsCleared;
      for (auto c : boards[curPlayer].board.at(i)) {
        if (c.getBlock()) { // if it is a player placed block instead of * in the middle column
          c.getBlock()->clearCell();
          if (!c.getBlock()->numCells()) { // if all cells in this block are removed
            playerScores[curPlayer] += (c.getBlock()->getLevel() + 1) * (c.getBlock()->getLevel() + 1); // get score for this block
            auto block = blocksOnBoard[curPlayer].begin();
            while (block->get() != c.getBlock()) ++block;
            blocksOnBoard[curPlayer].erase(block); // find the block in blocksOnBoard[curPlayer] and erase it
          }
        }
      }
    }
  }
  boards[curPlayer].board = newBoard;
  if (rowsCleared) {
    playerScores[curPlayer] += (playerLevels[curPlayer] + rowsCleared) * (playerLevels[curPlayer] + rowsCleared);
  }
  return rowsCleared;
}
*/
