#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

class Board;

class Block {
  Board *board;
  std::vector<std::vector<int>> pos;
  std::vector<int> lowerLeft;
  public:
    bool updatePos(int, int);
    virtual char getType() const = 0;
    Block(Board *, std::vector<std::vector<int>>, std::vector<int>);
    void rotate(bool);
};

class IBlock: public Block {
  public:
    IBlock(Board *);
    char getType() const override;
};

class JBlock: public Block {
  public:
    JBlock(Board *);
    char getType() const override;
};

class LBlock: public Block {
  public:
    LBlock(Board *);
    char getType() const override;
};

class OBlock: public Block {
  public:
    OBlock(Board *);
    char getType() const override;
};

class SBlock: public Block {
  public:
    SBlock(Board *);
    char getType() const override;
};

class ZBlock: public Block {
  public:
    ZBlock(Board *);
    char getType() const override;
};

class TBlock: public Block {
  public:
    TBlock(Board *);
    char getType() const override;
};
#endif
