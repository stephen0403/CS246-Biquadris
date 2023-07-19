#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H
#include <iostream>
#include "subject.h"

class absBoard;

class ConcreteSubject: public Subject {
  absBoard *board;

 public:
  explicit Concrete_Subject(absBoard *board);

  absBoard *&board();

  char getState(int row, int col) const override;

  ~Concrete_Subject();
};

#endif
