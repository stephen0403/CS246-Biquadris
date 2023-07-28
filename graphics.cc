#include "graphics.h"

const int maxgrid = 500;

GraphicObserver::GraphicObserver(Board *b1, Board *b2) : b1{b1}, b2{b2} {
  this->win.fillRectangle(0, 0, maxgrid, maxgrid, Xwindow::White);
}


void GraphicObserver::init() {


}
