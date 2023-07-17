#include "display.h"
#include "board.h"

Display::Display(Board *b1, Board *b2): bp1{b1}, bp2{b2} {}

Board *Display::getBoard(int i) const {
  if (i) {
    return bp1;
  } else {
    return bp2;
  }
}

static int numDigits(int num) {
  if (!num) return 1;
  int res = 0;
  while (num) {
    ++res;
    num /= 10;
  }
  return res;
}

std::ostream &operator<<(std::ostream &out, Display &display) {
  char separateHeader[10] = "        ";
  char separateFooter[20] = "                ";
  Board *bp1 = display.getBoard(1);
  Board *bp2 = display.getBoard(0);
  out << " Level:";
  int numSpaces = 5 - numDigits(bp1->getLevel());
  while (numSpaces) {
    out << ' ';
    --numSpaces;
  }
  out << bp1->getLevel();
  out << separateHeader;
  out << " Level:";
  numSpaces = 5 - numDigits(bp2->getLevel());
  while (numSpaces) {
    out << ' ';
    --numSpaces;
  }
  out << bp2->getLevel() << std::endl;
  out << " Score:";
  numSpaces = 5 - numDigits(bp1->getScore());
  while (numSpaces) {
    out << ' ';
    --numSpaces;
  }
  out << bp1->getScore();
  out << separateHeader;
  out << " Score:";
  numSpaces = 5 - numDigits(bp2->getScore());
  while (numSpaces) {
    out << ' ';
    --numSpaces;
  }
  out << bp2->getScore() << std::endl;
  out << "+-----------+" << separateHeader << "+-----------+" << std::endl;
  for (int i = 0; i < 18; ++i) {
    out << '|';
    for (auto c : bp1->getBoard().at(i)) {
      out << c;
    }
    out << '|';
    out << separateHeader;
    out << '|';
    for (auto c : bp2->getBoard().at(i)) {
      out << c;
    }
    out << '|';
    out << std::endl;
  }
  out << "+-----------+" << separateHeader << "+-----------+" << std::endl;
  return out << " Next:" << separateFooter << "Next:";
}

