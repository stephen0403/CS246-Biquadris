#ifndef _BLIND_H
#define _BLIND_H
#include "decorator.h"

class absBoard;

class blind: public Decorator {
public:
  blind(int row, int col, char character, absBoard *board); // top btm left right or just row and col?
  char tileAt(int row, int col, char character) override;
};

#endif
