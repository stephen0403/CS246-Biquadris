#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <string>
#include <memory>

class Block {
  // Board *board;
  std::vector<std::vector<int>> pos;
  std::vector<int> lowerLeft;
  int cellsLeft;
  protected:
    int level;
  friend class Board;
  public:
    virtual char getType() const = 0;
    Block(std::vector<std::vector<int>>, std::vector<int>, int);
    virtual std::string firstRow() const = 0;
    virtual std::string secondRow() const = 0;
    int numCells() const;
    void clearCell();
    int getLevel() const;
    std::vector<std::vector<int>> getPos();
};

class IBlock: public Block {
  public:
    IBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class JBlock: public Block {
  public:
    JBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class LBlock: public Block {
  public:
    LBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class OBlock: public Block {
  public:
    OBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class SBlock: public Block {
  public:
    SBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class ZBlock: public Block {
  public:
    ZBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class TBlock: public Block {
  public:
    TBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class StarBlock: public Block {
  public:
    StarBlock(int);
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

std::unique_ptr<Block> blockGen(char, int);
#endif
