#ifndef BLIND_H
#define BLIND_H

#include "decorator.h"

class Blind: public Decorator {
    bool blockDropped = false;
    char character;
  public:
    Blind(absBoard* board, char character);
    char tileAt(int row, int col) override;
    void setBlockDroppedTrue(); // this will set the blockDropped as true
    bool isHeavy() override;
    void rotateBlock(Block *block, bool clockwise) override;
    bool shift(int x, int y, Block *block, bool drop = false) override;
    void putBlock(int col, char type) override;
    int clearRows() override;
};

#endif
