#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "board.h"
#include "block.h"
#include "observer.h"
#include "window.h"

class GraphicDisplay : public Observer {
  Board *b1;
  Board *b2;
  Xwindow win1;
  Xwindow win2;
public:
  GraphicDisplay(Board *b1, Board *b2);
  void notify() override;
  ~GraphicDisplay();
};
