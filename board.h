#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>

struct Board {
  int numRows;
  int numCols;
  Board();
  std::vector<std::vector<char>> board;
  char tileAt(int row, int col); // for the decorator, can also use for display
};

#endif
