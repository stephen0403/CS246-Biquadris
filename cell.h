#ifndef _CELL_H_
#define _CELL_H_
#include <string>
class Block;

class Cell {
  Block *block;
  char type;
  public:
  Cell();
  void updateBlock(Block *, char);
  char getType() const;
  Block *getBlock() const;
};
#endif
