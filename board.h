#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include "block.h"
#include <string>

class Board {
  int level;
  int score;
  std::vector<std::vector<char>> board;
 public:
  Board(int);
  void clearRows();
  void updateScore();
  int getScore() const;
  int getLevel() const;
  std::vector<std::vector<char>> &getBoard();
};

#endif
