#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H
#include <iostream>
#include "subject.h"

class absBoard;

class Concrete_Subject: public Subject {
  absBoard *board;

 public:
  explicit Concrete_Subject(absBoard *board): board{board} {}

  absBoard *&board() { return board; }

  char getState(int row, int col) const override;

  ~Concrete_Subject();
};

#endif
