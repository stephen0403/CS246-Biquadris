#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <string>
#include <vector>
#include "observer.h"

class Board;
class Block;

class TextDisplay : public Observer {
  Board *b1;
  Board *b2;
  void printHeader(std::string, int) const;

public:
  TextDisplay(Board *b1, Board *b2);
  std::vector<Block*> queue;
  std::vector<int> currLevel;
  int currPlayer;
  void display(std::vector<Block*> &queue1, std::vector<Block*> &queue2, std::vector<int> currLevel, std::vector<int> currScore, bool p1blind = false, bool p2blind = false);
  void notify() override;
  ~TextDisplay();
};

#endif
