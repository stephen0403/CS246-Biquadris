#ifndef BLIND_H
#define BLIND_H

#include "decorator.h"

class Blind: public Decorator {
    bool blockDropped = false;
  public:
    Blind(absBoard* board);
    char tileAt(int row, int col);
    void setBlockDroppedTrue(); // this will set the blockDropped as true
}

#endif
