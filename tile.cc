#include "tile.h"
#include <iostream>
#include "subject.h"
#include "observer.h"
#include <string>
using namespace std;

// implement piece and occupied somewhere??


Tile::Tile(int x, int y, Board *board): x{x}, y{y}, occupied{false}, board{board} {}

int Tile::getX() { return x; }
int Tile::getY() { return y; }

char Tile::getState(int row, int col) const {
  return board->tileAt(row, col);
}

