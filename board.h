#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>

struct Board {
  int numRows;
  int numCols;
  Board();
  std::vector<std::vector<char>> board;
};

#endif
