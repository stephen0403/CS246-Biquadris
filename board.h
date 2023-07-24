#ifndef _BOARD_H_ // concrete subject and concrete component class
#define _BOARD_H_
#include <vector>
#include "absBoard.h"
#include "subject.h"
#include "block.h"

class Board: public absBoard, public Subject {
  int numRows;
  int numCols;
  std::vector<std::vector<char>> theBoard;
  absBoard *board;
  bool blindActivated = false;
  bool blockDroppedAfterBlind = false;
  bool dropped;
  public:
  Board(absBoard *board);
  char getState(int row, int col) const override;
  char tileAt(int row, int col) override;
  ~Board();
  void render();
  void rotateBlock(bool);
  bool shift(int x, int y, Block *block, bool drop = false);
};

#endif
