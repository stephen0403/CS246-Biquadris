#include "block.h"

Block::Block(std::vector<std::vector<int>> pos, std::vector<int> ll): /*board{b}, */pos{pos}, lowerLeft{ll} {}

IBlock::IBlock(/*Board *board*/): Block{/*board, */{{3, 0}, {3, 1}, {3, 2}, {3, 3}}, {3, 0}} {}

JBlock::JBlock(/*Board *board*/): Block{/*board, */{{2, 0}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}} {}

LBlock::LBlock(/*Board *board*/): Block{/*board, */{{2, 2}, {3, 0}, {3, 1}, {3, 2}}, {3, 0}} {}

OBlock::OBlock(/*Board *board*/): Block{/*board, */{{2, 0}, {2, 1}, {3, 0}, {3, 1}}, {3, 0}} {}

SBlock::SBlock(/*Board *board*/): Block{/*board, */{{2, 1}, {2, 2}, {3, 0}, {3, 1}}, {3, 0}} {}

ZBlock::ZBlock(/*Board *board*/): Block{/*board, */{{2, 0}, {2, 1}, {3, 1}, {3, 2}}, {3, 0}} {}

TBlock::TBlock(/*Board *board*/): Block{/*board, */{{2, 0}, {2, 1}, {2, 2}, {3, 1}}, {3, 0}} {}

// Board *Block::getBoard() const { return board; }

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

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char OBlock::getType() const { return 'O'; }

char ZBlock::getType() const { return 'Z'; }


std::unique_ptr<Block> blockGen(char res) {
  if (res == 'I') {
    return std::make_unique<IBlock>();
  } else if (res == 'J') {
    return std::make_unique<JBlock>();
  } else if (res == 'L') {
    return std::make_unique<LBlock>();
  } else if (res == 'T') {
    return std::make_unique<TBlock>();
  } else if (res == 'S') {
    return std::make_unique<SBlock>();
  } else if (res == 'Z') {
    return std::make_unique<ZBlock>();
  } else { 
    return std::make_unique<OBlock>();
  }
}

