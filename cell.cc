#include "cell.h"

Cell::Cell(): block{nullptr}, type{' '} {}

void Cell::updateBlock(Block *b, char t) {
  block = b;
  type = t;
}

char Cell::getType() const { return type; }

Block *Cell::getBlock() const { return block; }
