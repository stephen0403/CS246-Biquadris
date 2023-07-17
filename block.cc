#include "board.h"
#include <iostream>

Block::Block(Board *b, std::vector<std::vector<int>> pos, std::vector<int> ll): board{b}, pos{pos}, lowerLeft{ll} {}

IBlock::IBlock(Board *board): Block{board, {{3, 0}, {3, 1}, {3, 2}, {3, 3}}, {3, 0}} {}

JBlock::JBlock(Board *board): Block{board, {{2, 0}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}} {}

LBlock::LBlock(Board *board): Block{board, {{2, 2}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}} {}

OBlock::OBlock(Board *board): Block{board, {{2, 0}, {2, 1}, {3, 0}, {3, 1}}, {3, 0}} {}

SBlock::SBlock(Board *board): Block{board, {{3, 1}, {3, 2}, {4, 0}, {4, 1}}, {4, 0}} {}

ZBlock::ZBlock(Board *board): Block{board, {{3, 0}, {3, 1}, {4, 1}, {4, 2}}, {4, 0}} {}

TBlock::TBlock(Board *board): Block{board, {{3, 0}, {3, 1}, {3, 2}, {4, 1}}, {4, 0}} {}

bool Block::updatePos(int x, int y) {
  for (int i = 0; i < 4; ++i) {
    board->getBoard().at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    if (pos[i][0] + y > 17 || pos[i][1] + x < 0 || pos[i][1] + x > 10 ||
        board->getBoard().at(pos[i][0] + y).at(pos[i][1] + x) != ' ') {
      for (int i = 0; i < 4; ++i) {
        board->getBoard().at(pos[i][0]).at(pos[i][1]) = getType();
      }
      return false;
    }
  }
  lowerLeft[0] += y;
  lowerLeft[1] += x;
  for (int i = 0; i < 4; ++i) {
    pos[i][0] += y;
    pos[i][1] += x;
    board->getBoard().at(pos[i][0]).at(pos[i][1]) = getType();
  }
  return true;
}

void Block::rotate(bool clockwise) {
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
    board->getBoard().at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    dest[i][0] += lowerLeft[0] - newLowerLeft[0];
    dest[i][1] += lowerLeft[1] - newLowerLeft[1];
    if (dest[i][1] > 10 || board->getBoard().at(dest[i][0]).at(dest[i][1]) != ' ') {
      for (int i = 0; i < 4; ++i) {
        board->getBoard().at(pos[i][0]).at(pos[i][1]) = getType();
      }
      return;
    }
  }
  for (int i = 0; i < 4; ++i) {
    pos[i][0] = dest[i][0];
    pos[i][1] = dest[i][1];
    board->getBoard().at(pos[i][0]).at(pos[i][1]) = getType();
  }
}

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char OBlock::getType() const { return 'O'; }

char ZBlock::getType() const { return 'Z'; }

