#ifndef _BLIND_H
#define _BLIND_H
#include "decorator.h"

class absBoard;

class blind: public Decorator {
public:
  blind(char character, absBoard *board); // top btm left right or just row and col?
  char tileAt(int row, int col) override;
};

#endif
