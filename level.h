#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "board.h"

class Level {
    Board *board;
protected:
    Block *createBlock(char type);
public:
    Level(Board *board);
    virtual Block *generateBlock() = 0;
};

#endif
