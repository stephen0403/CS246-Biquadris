#include "board.h"
#include "block.h"
// #include <sstream>

// board is ptr to absBoard
// theBoard is the vec vec char board

Board::Board(absBoard *board): numRows{18}, numCols{11}, board(board), theBoard(numRows, std::vector<char>(numCols, ' ')) {
  shift(0, 0, false);
}

char Board::tileAt(int row, int col) { return theBoard.at(row).at(col); }

Board::~Board() {}

void Board::render() {
  notifyObservers();
}

char Board::getState(int row, int col) {
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


bool Board::shift(int x, int y, bool drop, Block *block) {
  // auto block = queue.front().get();
  std::vector<std::vector<int>> &pos = block->pos;
  for (int i = 0; i < 4; ++i) {
    board.at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    if (pos[i][0] + y >= numRows || pos[i][1] + x < 0 || pos[i][1] + x >= numCols ||
        board.at(pos[i][0] + y).at(pos[i][1] + x) != ' ') {
      if (y && drop) {
        dropped = true;
        for (int i = 0; i < 4; ++i) {
          if (block->pos[i][0] < 3) {
            for (int i = 0; i < 4; ++i) {
              block->pos[i][0] += y;
              block->pos[i][1] += x;
              board.at(pos[i][0]).at(pos[i][1]) = block->getType();
            }
            throw; // winner
          }
        }
      }
      for (int i = 0; i < 4; ++i) {
        board.at(pos[i][0]).at(pos[i][1]) = block->getType();
      }
      return false;
    }
  }
  block->lowerLeft[0] += y;
  block->lowerLeft[1] += x;
  for (int i = 0; i < 4; ++i) {
    block->pos[i][0] += y;
    block->pos[i][1] += x;
    board.at(pos[i][0]).at(pos[i][1]) = block->getType();
  }
  return true;
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
