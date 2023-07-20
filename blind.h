#ifndef _BLIND_H
#define _BLIND_H
#include "decorator.h"

class absBoard;

class blind: public Decorator {
public:
  blind(char character, absBoard *board); 
  char tileAt(int row, int col) override;
};

#endif
