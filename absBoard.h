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
};

#endif
