#ifndef ABS_BOARD_H
#define ABS_BOARD_H

#include <vector>

class Board;
class Block;

// Some Global Constants

const int COLUMNS = 11;
const int ROWS = 15;

class absBoard {
public:
    virtual char tileAt(int row, int col) = 0;
    virtual ~absBoard();
    virtual bool swapBlock(Block *oldBlock, Block *newBlock) = 0;
    virtual void rotateBlock(Block *block, bool clockwise) = 0;
    virtual int shift(int x, int y, Block *block, bool drop = false) = 0;
    virtual void putBlock(int col, char type) = 0;
    virtual int clearRows(std::vector<int> &playerScores, int currPlayer) = 0;
    virtual bool isHeavy() = 0;
    virtual void setHeavy() = 0;
    virtual void triggerBlind() = 0;
    virtual bool isBlind() = 0;
};

#endif
