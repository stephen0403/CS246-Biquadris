// #ifndef _TEXT_H_
// #define _TEXT_H_
// #include <iostream>
// #include "observer.h"

// class absBoard;
// class Block;
// class Tile;

// class TextDisplay: public Observer {
//   absBoard *b1;
//   absBoard *b2;
//   public:
//   TextDisplay(absBoard *, absBoard *);
//   // void notify(Tile &);
//   void notify() override;
//   void blind(size_t, std::ostream &);
//   void changePreviews(Block *, size_t);
//   void printPreviews(std::ostream &);
// };

// #endif
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <string>
#include "observer.h"

class Board;
class Block;

class TextDisplay : public Observer {
  Board *b1;
  Board *b2
  void printHeader(std::string, int) const;
  public:
  TextDisplay(Board *b1, Board *b2);
  void display(std::vector<Block*> &queue);
};

#endif
