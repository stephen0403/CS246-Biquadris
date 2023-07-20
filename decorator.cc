#include "decorator.h"

Decorator::Decorator(absBoard* board, int row, int col, char character)
  : board{board}, row{row}, col{col}, character{character} {}

Decorator::~Decorator() {

}
