#include "board.h"

static bool isFull(std::vector<char> &row) {
  for (auto c : row) {
    if (c == ' ') {
      return false;
    }
  }
  return true;
}

void Board::clearRows() {
  std::vector<std::vector<char>> newBoard(18, std::vector<char>(11, ' '));
  int cur_row = 17;
  for (int i = 17; i >= 3; i--) {
    if (!isFull(board.at(i))) {
      newBoard.at(cur_row) = board.at(i);
      --cur_row;
    }
  }
  board = newBoard;
}

Board::Board(int lvl): level{lvl}, score{0}, board(18, std::vector<char>(11, ' ')) {}
  //current = std::make_unique<JBlock>(JBlock(this));
  //current->updatePos(0, 0);
//}

int Board::getScore() const { return score; }

int Board::getLevel() const { return level; }
/*
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
*/


void Board::updateScore() {
  for (auto &row : board) {
    if (isFull(row)) {
      ++score;
    }
  }
  score += level;
}

std::vector<std::vector<char>> &Board::getBoard() {
  return board;
}

char Board::tileAt(int row, int col) {
  return board.at(row).at(col);
}
