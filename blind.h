#ifndef _BLIND_H
#define _BLIND_H
#include "decorator.h"

class absBoard;

class blind: public Decorator {
public:
  blind(int length, int width, char character, absBoard *board);
  char tileAt(int length, int width) override;
};

#endif
