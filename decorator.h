#ifndef DECORATOR_H
#define DECORATOR_H

#include absBoard.h 

class Decorator: public absBoard {
  protected:
    absBoard* board;
    int row;
    int col;
    char character;
  public:
    Decorator(absBoard* board, int row, int col, char character);
    virtual ~Decorator(); // Note: destructor does not do anything. Client must 
};                        // deallocate component through the use of smart pointers
