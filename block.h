#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <string>
#include <memory>

class Block {
  // Board *board;
  std::vector<std::vector<int>> pos;
  std::vector<int> lowerLeft;
  friend class Board;
  public:
    virtual char getType() const = 0;
    Block(std::vector<std::vector<int>>, std::vector<int>);
    virtual std::string firstRow() const = 0;
    virtual std::string secondRow() const = 0;
    // Board *getBoard() const;
};

class IBlock: public Block {
  public:
    IBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class JBlock: public Block {
  public:
    JBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class LBlock: public Block {
  public:
    LBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class OBlock: public Block {
  public:
    OBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class SBlock: public Block {
  public:
    SBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class ZBlock: public Block {
  public:
    ZBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

class TBlock: public Block {
  public:
    TBlock();
    char getType() const override;
    std::string firstRow() const override;
    std::string secondRow() const override;
};

std::unique_ptr<Block> blockGen(char);
#endif
