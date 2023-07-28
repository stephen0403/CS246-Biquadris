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
};

#endif
