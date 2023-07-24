#ifndef _TEXT_H_
#define _TEXT_H_
#include <iostream>
#include "observer.h"

class absBoard;
class Block;
class Tile;

class TextDisplay: public Observer {
  absBoard *b1;
  absBoard *b2;
  public:
  TextDisplay(absBoard *, absBoard *);
  // void notify(Tile &);
  void notify() override;
  void blind(size_t, std::ostream &);
  void changePreviews(Block *, size_t);
  void printPreviews(std::ostream &);
};

#endif
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <string>

class GamePlay;

class TextDisplay {
  GamePlay *game;
  void printHeader(std::string, int) const;
  public:
  TextDisplay(GamePlay *);
  void display();
};

#endif
