#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include "block.h"
#include <string>

class Board : public absBoard {
  int level;
  int score;
  std::vector<std::vector<char>> board;
 public:
  Board(int);
  void clearRows();
  void updateScore();
  int getScore() const;
  int getLevel() const;
  char tileAt(int row, int col); // for the decorator, can also use for display
  std::vector<std::vector<char>> &getBoard();
};

#endif
