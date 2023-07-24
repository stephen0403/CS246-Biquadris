#ifndef ABS_BOARD_H
#define ABS_BOARD_H

class Board;

// Some Global Constants

const int COLUMNS = 11;
const int ROWS = 15;

class absBoard {
public:
    virtual char tileAt(int row, int col) = 0;
    virtual ~absBoard();
    virtual void rotateBlock(bool) = 0;
    virtual bool shift(int x, int y, Block *block, bool drop = false) = 0;
};

#endif
