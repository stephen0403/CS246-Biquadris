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

TextDisplay::~TextDisplay() {
  // do nothing
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


void TextDisplay::display(const std::vector<Block*> &queue1, const std::vector<Block*> &queue2, std::vector<int> currLevel, std::vector<int> currScore, bool p1blind, bool p2blind) {
  std::string separateHeader{"        "};
  std::string separateFooter{"                "};
  std::string emptyNext{"                     "};
  std::string border{"+-----------+"};
  auto bp1 = b1;
  auto bp2 = b2;
  printHeader(" Level:", currLevel.at(0));
  std::cout << separateHeader;
  printHeader(" Level:", currLevel.at(1));
  std::cout << std::endl;
  printHeader(" Score:", currScore.at(0));
  std::cout << separateHeader;
  printHeader(" Score:", currScore.at(1));
  std::cout << std::endl;
  std::cout << border << separateHeader << border << std::endl;
  if (p1blind && p2blind) {
    for (int i = 0; i < 18; ++i) {
      std::cout << '|';
      for (int c = 0; c < 16; c++) {
        if (c >= 2 && c <= 8 && i >= 5 && i <= 14) {
          std::cout << "?";
        }
        else {
          std::cout << bp1->theBoard.at(i).at(c).getType();
        }
      }
      std::cout << '|' << separateHeader << '|';
      for (int c = 0; c < 16; c++) {
        if (c >= 2 && c <= 8 && i >= 5 && i <= 14) {
          std::cout << "?";
        }
        else {
          std::cout << std::cout << bp2->theBoard.at(i).at(c).getType();
        }
      }
      std::cout << '|' << std::endl;
    }
  } else if (p1blind && !p2blind) {
    for (int i = 0; i < 18; ++i) {
      std::cout << '|';
      for (int c = 0; c < 16; c++) {
        if (c >= 2 && c <= 8 && i >= 5 && i <= 14) {
          std::cout << "?";
        }
        else {
          std::cout << bp1->theBoard.at(i).at(c).getType();
        }
      }
      std::cout << '|' << separateHeader << '|';
      for (auto c : bp2->theBoard.at(i)) {
        std::cout << c.getType();
      }
      std::cout << '|' << std::endl;
    }
  } else if (!p1blind && p2blind) {
    for (int i = 0; i < 18; ++i) {
      std::cout << '|';
      for (auto c : bp1->theBoard.at(i)) {
        std::cout << c.getType();
      }
      std::cout << '|' << separateHeader << '|';
      for (int c = 0; c < 16; c++) {
        if (c >= 2 && c <= 8 && i >= 5 && i <= 14) {
          std::cout << "?";
        }
        else {
          std::cout << bp2->theBoard.at(i).at(c).getType();
        }
      }
      std::cout << '|' << std::endl;
    }
  } else {
    for (int i = 0; i < 18; ++i) {
      std::cout << '|';
    for (int k = 0; k < 11; ++k) {
      std::cout << b1->tileAt(i, k);
    }
    std::cout << '|' << separateHeader << '|';
    for (int k = 0; k < 11; ++k) {
      std::cout << b2->tileAt(i, k);
    }
    std::cout << '|' << std::endl;
    }
  }
  std::cout << border << separateHeader << border << std::endl;
  std::cout << " Next:" << separateFooter << "Next:" << std::endl; // change game->queue..... to be the next blocks queue

  // Print out Next blocks for both players based on their respective block queues
  std::cout << queue1.at(1)->firstRow(); 
  std::cout << emptyNext << queue2.at(1)->firstRow() << std::endl;
  std::cout << queue1.at(1)->secondRow();
  std::cout << emptyNext << queue2.at(1)->secondRow() << std::endl;
}

// void TextDisplay::display(std::vector<Block*> &queue1, std::vector<Block*> &queue2, std::vector<int> currLevel) {
//   std::string separateHeader{"        "};
//   std::string separateFooter{"                "};
//   std::string emptyNext{"                     "};
//   std::string border{"+-----------+"};
//   printHeader(" Level:", currLevel.at(0));
//   std::cout << separateHeader;
//   printHeader(" Level:", currLevel.at(1));
//   std::cout << std::endl;
//   printHeader(" Score:", 0);
//   std::cout << separateHeader;
//   printHeader(" Score:", 0);
//   std::cout << std::endl;
//   std::cout << border << separateHeader << border << std::endl;
//   for (int i = 0; i < 18; ++i) {
//     std::cout << '|';
//     for (int k = 0; k < 11; ++k) {
//       std::cout << b1->tileAt(i, k);
//     }
//     std::cout << '|' << separateHeader << '|';
//     for (int k = 0; k < 11; ++k) {
//       std::cout << b2->tileAt(i, k);
//     }
//     std::cout << '|' << std::endl;
//   }
//   std::cout << border << separateHeader << border << std::endl;
//   std::cout << " Next:" << separateFooter << "Next:" << std::endl; // change game->queue..... to be the next blocks queue

//   // Print out Next blocks for both players based on their respective block queues
//   std::cout << queue1.at(1)->firstRow(); 
//   std::cout << emptyNext << queue2.at(1)->firstRow() << std::endl;
//   std::cout << queue1.at(1)->secondRow();
//   std::cout << emptyNext << queue2.at(1)->secondRow() << std::endl;
// }

void TextDisplay::notify() {
  // display(queue1, queue2, currLevel);
}
