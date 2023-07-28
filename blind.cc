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


void Blind::isHeavy() {
  return heavy;
}

bool Blind::shift(int x, int y, Block *block, bool drop) {
  // auto block = queue.front().get();
  std::vector<std::vector<int>> &pos = block->pos;
  for (int i = 0; i < 4; ++i) {  
    theBoard.at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    if (pos[i][0] + y >= numRows || pos[i][1] + x < 0 || pos[i][1] + x >= numCols ||
        theBoard.at(pos[i][0] + y).at(pos[i][1] + x) != ' ') {
      if (y && drop) {
        for (int i = 0; i < 4; ++i) {
          if (block->pos[i][0] < 3) {
            for (int i = 0; i < 4; ++i) {
              block->pos[i][0] += y;
              block->pos[i][1] += x;
              theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
            }
            throw; // winner
          }
        }
      }
      for (int i = 0; i < 4; ++i) {
        theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
      }
      return false;
    }
  }
  block->lowerLeft[0] += y;
  block->lowerLeft[1] += x;
  for (int i = 0; i < 4; ++i) {
    block->pos[i][0] += y;
    block->pos[i][1] += x;
    theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
  }
  return true;
}


int Blind::clearRows() {
  int rowsCleared = 0;
  for (int i = numRows - 1; i >= 0; i--) {
    if (isFull(theBoard.at(i))) {
      rowsCleared++;
      for (int j = i; j > 0; j--) {
        theBoard.at(j) = theBoard.at(j - 1);
      }
      i++;
    }
  }
  return rowsCleared;
}

void Blind::rotateBlock(Block *block, bool clockwise) {
  // auto block = queue.front().get();
  std::vector<std::vector<int>> &pos = block->pos;
  int dest[4][2];
  if (clockwise) {
    for (int i = 0; i < 4; ++i) {
      dest[i][0] = pos[i][1];
      dest[i][1] = -pos[i][0];
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      dest[i][0] = -pos[i][1];
      dest[i][1] = pos[i][0];
    }
  }
  int newLowerLeft[2] = {dest[0][0], dest[0][1]};
  for (int i = 0; i < 4; ++i) {
    if (dest[i][0] > newLowerLeft[0]) {
      newLowerLeft[0] = dest[i][0];
    }
    if (dest[i][1] < newLowerLeft[1]) {
      newLowerLeft[1] = dest[i][1];
    }
  }
  for (int i = 0; i < 4; ++i) {
    theBoard.at(pos[i][0]).at(pos[i][1]) = ' ';
  }
  for (int i = 0; i < 4; ++i) {
    dest[i][0] += block->lowerLeft[0] - newLowerLeft[0];
    dest[i][1] += block->lowerLeft[1] - newLowerLeft[1];
    if (dest[i][1] >= numCols || theBoard.at(dest[i][0]).at(dest[i][1]) != ' ') {
      for (int i = 0; i < 4; ++i) {
        theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
      }
      return;
    }
  }
  for (int i = 0; i < 4; ++i) {
    block->pos[i][0] = dest[i][0];
    block->pos[i][1] = dest[i][1];
    theBoard.at(pos[i][0]).at(pos[i][1]) = block->getType();
  }
}

void Blind::putBlock(int col, char type) {
  for (int i = 3; i < 18; ++i) {
    if (theBoard.at(i).at(5) != ' ') {
      if (i > 3) {
        theBoard.at(i - 1).at(col) = type;
        return;
      } else {
        throw; // throw what? Orginally curplayer
      }
    }
  }
}
