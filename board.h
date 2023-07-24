#ifndef _BOARD_H_ // concrete subject and concrete component class
#define _BOARD_H_
#include <vector>
#include "absBoard.h"
#include "subject.h"

class Board: public absBoard, public Subject {
  int numRows;
  int numCols;
  // std::vector<std::vector<char>> board;
  absBoard *board;
  bool blindActivated = false;
  bool blockDroppedAfterBlind = false;
  public:
  explicit Board(absBoard *board): board{board} {}
  char getState(int row, int col) const override;
  char tileAt(int row, int col) override;
  ~Board();
  void render();
};

#endif
