#include "tile.h"
#include <iostream>
#include "subject.h"
#include "observer.h"
#include <string>
#include "absboard.h"
using namespace std;

void Tile::render() {
  notifyObservers();
}

// <<<<<<< decorator
// void Tile::render() {
//   notifyObservers();
// }

// Tile::Tile(int x, int y, absBoard *board): x{x}, y{y}, board{board} {}
// =======
// Tile::Tile(int x, int y, Board *board): x{x}, y{y}, isOccupied{false}, board{board} {}
// >>>>>>> main

int Tile::getX() { return x; }
int Tile::getY() { return y; }

char Tile::getState(int row, int col) const {
  return board->tileAt(row, col);
}
