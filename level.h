#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "board.h"

class Level {
    Board *board;

public:
    Level(Board *board);
    Block *createBlock(char type);
    virtual Block *generateBlock() = 0;
};

#endif
