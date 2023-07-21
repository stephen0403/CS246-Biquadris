#include "blind.h"
#include "absboard.h"
#include <iostream>

static const int COLUMN_LEFT = 3;
static const int COLUMN_RIGHT = 9;
static const int ROW_TOP = 3;
static const int ROW_BOTTOM = 12;

blind::blind(char character, absBoard *board, )
  : Decorator{board, character} {}

char blind::tileAt(int row, int col) {

  // something along the lines of if in bounds of where it should be covered with ???, then return character
  // else return under
  
  char under = board->tileAt(row, col);
  rowBounds = row >= 2 && row <= 8; // put which tiles should be covered // are we starting 0 index or 1 index?
  colBounds = col >= 2 && <= 11;

  if (rowBounds && colBounds) {
    return character;
  }
  else {
    return under;
  }
};
