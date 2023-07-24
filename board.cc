#include "board.h"
// #include <sstream>


Board::Board(): numRows{18}, numCols{11}, board(numRows, std::vector<char>(numCols, ' ')) {}

char Board::tileAt(int row, int col) { return board.at(row).at(col); }

Board::~Board() {}

void Board::render() {
  notifyObservers();
}

char Board::getState() {
  return board->tileAt(row, col);
}

  //current = std::make_unique<JBlock>(JBlock(this));
  //current->updatePos(0, 0);
//}
/*
std::string Board::getScore() const {
  std::ostringstream res;
  res << " Score:";
  int numSpaces = 5 - numDigits(score);
  while (numSpaces) {
    res << " ";
    --numSpaces;
  }
  res << score;
  return res.str();
}



void Board::move(int x, int y) {
  current->updatePos(x, y);
}

void Board::rotate(bool clockwise) {
  current->rotate(clockwise);
  current->updatePos(0, 0);
}

void Board::updateCurrent() {
  current = next;
}



void Board::updateScore() {
  for (auto &row : board) {
    if (isFull(row)) {
      ++score;
    }
  }
  score += level;
}
*/

