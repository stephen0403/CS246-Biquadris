// #include "block.h"
// #include "board.h"

// class Level {
//     int curLevel;

// protected:
//     Board *board;
// public:
//     Level(Board *board): board{board} {};
//     virtual Block *generateBlock() = 0;
// };


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
