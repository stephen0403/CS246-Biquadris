#ifndef ABS_BOARD_H
#define ABS_BOARD_H

class Board;

class absBoard {
public:
    virtual char tileAt(int row, int col) = 0;
    virtual ~absBoard();
};

#endif
