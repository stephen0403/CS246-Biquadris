#include "block.h"
#include "board.h"

class Level {
    int curLevel;

protected:
    Board *board;
public:
    Level(Board *board): board{board} {};
    virtual Block *generateBlock() = 0;
};
