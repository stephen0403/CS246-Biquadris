// #include "text.h"
// #include "board.h"
// #include "block.h"
// #include <iostream>
// #include <sstream>

// TextDisplay::TextDisplay(Board *b1, Board *b2, ): b1{} {}



/*
static int numDigits(int num) {
  if (!num) return 1;
  int res = 0;
  while (num) {
    ++res;
    num /= 10;
  }
  return res;
}

void TextDisplay::printHeader(std::string title, int num) const {
  // std::ostringstream res;
  std::cout << title;
  int numSpaces = 5 - numDigits(num);
  while (numSpaces) {
    std::cout << " ";
    --numSpaces;
  }
  std::cout << num;
}

void TextDisplay::display() {
  std::string separateHeader{"        "};
  std::string separateFooter{"                "};
  std::string emptyNext{"                     "};
  std::string border{"+-----------+"};
  auto bp1 = game->boards[0].board;
  auto bp2 = game->boards[1].board;
  printHeader(" Level:", game->playerLevels[0]);
  std::cout << separateHeader;
  printHeader(" Level:", game->playerLevels[1]);
  std::cout << std::endl;
  printHeader(" Score:", game->playerScores[0]);
  std::cout << separateHeader;
  printHeader(" Score:", game->playerScores[1]);
  std::cout << std::endl;
  std::cout << border << separateHeader << border << std::endl;
  for (int i = 0; i < 18; ++i) {
    std::cout << '|';
    for (auto c : bp1.at(i)) {
      std::cout << c;
    }
    std::cout << '|' << separateHeader << '|';
    for (auto c : bp2.at(i)) {
      std::cout << c;
    }
    std::cout << '|' << std::endl;
  }
  std::cout << border << separateHeader << border << std::endl;
  std::cout << " Next:" << separateFooter << "Next:" << std::endl;
  if (game->curPlayer) {
    std::cout << game->queue.at(1)->firstRow() << std::endl << game->queue.at(1)->secondRow() << std::endl;
  } else {
    std::cout << emptyNext << game->queue.at(1)->firstRow() << std::endl;
    std::cout << emptyNext << game->queue.at(1)->secondRow() << std::endl;
  }
}
*/
#include "text.h"
#include "board.h"
#include "block.h"
#include <iostream>
#include <sstream>

TextDisplay::TextDisplay(Board *b1, Board *b2): b1{b1}, b2{b2} {}

static int numDigits(int num) {
  if (!num) return 1;
  int res = 0;
  while (num) {
    ++res;
    num /= 10;
  }
  return res;
}

void TextDisplay::printHeader(std::string title, int num) const {
  // std::ostringstream res;
  std::cout << title;
  int numSpaces = 5 - numDigits(num);
  while (numSpaces) {
    std::cout << " ";
    --numSpaces;
  }
  std::cout << num;
}

void TextDisplay::display() {
  std::string separateHeader{"        "};
  std::string separateFooter{"                "};
  std::string emptyNext{"                     "};
  std::string border{"+-----------+"};
  auto bp1 = b1;
  auto bp2 = b2;
  printHeader(" Level:", "filler 1");
  std::cout << separateHeader;
  printHeader(" Level:", "filler 2");
  std::cout << std::endl;
  printHeader(" Score:", "filler 3");
  std::cout << separateHeader;
  printHeader(" Score:", "filler 4");
  std::cout << std::endl;
  std::cout << border << separateHeader << border << std::endl;
  for (int i = 0; i < 18; ++i) {
    std::cout << '|';
    for (auto c : bp1.at(i)) {
      std::cout << c;
    }
    std::cout << '|' << separateHeader << '|';
    for (auto c : bp2.at(i)) {
      std::cout << c;
    }
    std::cout << '|' << std::endl;
  }
  std::cout << border << separateHeader << border << std::endl;
  std::cout << " Next:" << separateFooter << "Next:" << std::endl;
  if (game->curPlayer) { ///////////////////////// JUST NEED TO CHANGE THIS NOW
    std::cout << game->queue.at(1)->firstRow() << std::endl << game->queue.at(1)->secondRow() << std::endl;
  } else {
    std::cout << emptyNext << game->queue.at(1)->firstRow() << std::endl;
    std::cout << emptyNext << game->queue.at(1)->secondRow() << std::endl;
  }
}
