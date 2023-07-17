#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <iostream>

class Board;

class Display {
  Board *bp1;
  Board *bp2;
  public:
  Display(Board *, Board *);
  Board *getBoard(int) const;
};

std::ostream &operator<<(std::ostream &, Display &);
#endif
