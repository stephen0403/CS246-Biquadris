#include "blind.h"
#include "absboard.h"
#include <iostream>

blind::blind(int row, int col, char character, absBoard *board)
  : Decorator{board, row, col, character} {}

char blind::tileAt(int row, int col, char character) {


};
