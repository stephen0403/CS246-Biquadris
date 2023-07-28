#ifndef DECORATOR_H
#define DECORATOR_H

#include "absBoard.h" 

class Decorator: public absBoard {
  protected:
    absBoard* component;
  public:
    Decorator(absBoard* board);
    virtual char tileAt(int row, int tile) = 0;
    virtual ~Decorator() = 0; // Note: destructor does not do anything. Client must 
};                            // deallocate component through the use of smart pointers

#endif
