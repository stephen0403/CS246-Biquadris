#include "window.h"
#include <memory>
#include "cell.h"
#include <vector>
#include "board.h"

class GamePlay;

class Graphics {
  std::unique_ptr<Xwindow> window;
  Board* b1;
  Board* b2;
  std::vector<int> levels;
  int currPlayer;
  std::vector<int> scores;
  std::vector<Block*> &queue1;
  std::vector<Block*> &queue2;
  public:
  Graphics(Board* b1, Board* b2, std::vector<int> levels, int currPlayer, std::vector<int> scores, std::vector<Block*> &queue1, std::vector<Block*> &queue2);
  void updateBoard();
};
