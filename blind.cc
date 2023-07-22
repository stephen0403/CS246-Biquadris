#include "blind.h"
#include "absboard.h"
#include <iostream>

static const int COLUMN_LEFT = 3;
static const int COLUMN_RIGHT = 9;
static const int ROW_TOP = 3;
static const int ROW_BOTTOM = 12;

Blind::Blind(absBoard *board, char character): Decorator{board}, character{character} {}

char Blind::tileAt(int row, int col) {

  // something along the lines of if in bounds of where it should be covered with ???, then return character
  // else return under
  
  static char under = component->tileAt(row, col);
  static bool rowBounds = row >= ROW_TOP && row <= ROW_BOTTOM; // put which tiles should be covered // are we starting 0 index or 1 index?
  static bool colBounds = col >= COLUMN_LEFT && col <= COLUMN_RIGHT;

  if (rowBounds && colBounds && !blockDropped) {
    return character; // feed in ? for character
  }
  else {
    return under;
  }
}

void Blind::setBlockDroppedTrue() {
    blockDropped = true;
}
