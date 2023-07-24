#ifndef _TILE_H // concrete subject
#define _TILE_H
#include <iostream>
#include "subject.h"

class absBoard;

class Tile: public Subject {
  int x;
  int y;
  absBoard *board; // which players board
  char piece;
  bool occupied = false;
  bool blindActivated = false;
  bool blockDroppedAfterBlind = false;

 public:
  Tile(int x, int y, absBoard *board);
  // absBoard *&board() { return board; }
  char getState(int row, int col) const override;
  int getX();
  int getY();
  bool isOccupied();
  ~Tile();
};

#endif
