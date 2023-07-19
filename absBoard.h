#ifndef ABS_BOARD_H
#define ABS_BOARD_H

class Board;

class absBoard {
public:
    virtual char tileAt(Board &board) = 0;
    virtual ~absBoard();
};

#endif
