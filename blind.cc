#include "blind.h"
#include "absboard.h"
#include <iostream>

blind::blind(int row, int col, char character, absBoard *board)
  : Decorator{board, row, col, character} {}

char blind::tileAt(int row, int col) {
  char under = board->tileAt(row, col);
  bounds = '' // put which tiles should be covered

  // something along the lines of if in bounds of where it should be covered with ???, then return character
  // else return under

};
