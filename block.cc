#include "block.h"

Block::Block(std::vector<std::vector<int>> pos, std::vector<int> ll, int level): /*board{b}, */pos{pos}, level{level}, lowerLeft{ll}, cellsLeft{4} {}

IBlock::IBlock(int level): Block{/*board, */{{3, 0}, {3, 1}, {3, 2}, {3, 3}}, {3, 0}, level} {}

JBlock::JBlock(int level): Block{/*board, */{{2, 0}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}, level} {}

LBlock::LBlock(int level): Block{/*board, */{{2, 2}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}, level} {}

OBlock::OBlock(int level): Block{/*board, */{{2, 0}, {2, 1}, {3, 0}, {3, 1}}, {3, 0}, level} {}

SBlock::SBlock(int level): Block{/*board, */{{2, 1}, {2, 2}, {3, 0}, {3, 1}}, {3, 0}, level} {}

ZBlock::ZBlock(int level): Block{/*board, */{{2, 0}, {2, 1}, {3, 1}, {3, 2}}, {3, 0}, level} {}

TBlock::TBlock(int level): Block{/*board, */{{2, 0}, {2, 1}, {2, 2}, {3, 1}}, {3, 0}, level} {}

StarBlock::StarBlock(int level): Block{/*board, */{{1, 5}, {1, 5}, {1, 5}, {1, 5}}, {1, 5}, level} {}

int Block::numCells() const { return cellsLeft; }

void Block::clearCell() { --cellsLeft; }

int Block::getLevel() const { return level; }

std::string StarBlock::firstRow() const { return "    "; }

std::string StarBlock::secondRow() const { return " * "; }

std::string IBlock::firstRow() const { return " IIII"; }

std::string IBlock::secondRow() const { return "     "; }

std::string JBlock::firstRow() const { return " J   "; }

std::string JBlock::secondRow() const { return " JJJ "; }

std::string LBlock::firstRow() const { return "   L "; }

std::string LBlock::secondRow() const { return " LLL "; }

std::string OBlock::firstRow() const { return " OO  "; }

std::string OBlock::secondRow() const { return " OO  "; }

std::string TBlock::firstRow() const { return " TTT "; }

std::string TBlock::secondRow() const { return "  T  "; }

std::string SBlock::firstRow() const { return "  SS "; }

std::string SBlock::secondRow() const { return " SS  "; }

std::string ZBlock::firstRow() const { return " ZZ  "; }

std::string ZBlock::secondRow() const { return "  ZZ "; }

char StarBlock::getType() const { return '*'; }

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char OBlock::getType() const { return 'O'; }

char ZBlock::getType() const { return 'Z'; }

std::vector<std::vector<int>> Block::getPos() { 
  return pos;
}


std::unique_ptr<Block> blockGen(char res, int level) {
  if (res == 'I') {
    return std::make_unique<IBlock>(level);
  } else if (res == 'J') {
    return std::make_unique<JBlock>(level);
  } else if (res == 'L') {
    return std::make_unique<LBlock>(level);
  } else if (res == 'T') {
    return std::make_unique<TBlock>(level);
  } else if (res == 'S') {
    return std::make_unique<SBlock>(level);
  } else if (res == 'Z') {
    return std::make_unique<ZBlock>(level);
  } else if (res == '*') {
    return std::make_unique<StarBlock>(level);
  } else { 
    return std::make_unique<OBlock>(level);
  }
}
