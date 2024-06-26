#include "graphics.h"
#include <string>
#include <sstream>

static const int COLUMN_LEFT = 3;
static const int COLUMN_RIGHT = 9;
static const int ROW_TOP = 3;
static const int ROW_BOTTOM = 12;

// what does this mean
static Xwindow::Color typeToColor(std::string type) {
  if (type == "I") return Xwindow::Cyan;
  if (type == "J") return Xwindow::Blue;
  if (type == "L") return Xwindow::Orange;
  if (type == "O") return Xwindow::Yellow;
  if (type == "S") return Xwindow::Green;
  if (type == "T") return Xwindow::Magenta;
  if (type == "Z") return Xwindow::Red;
  if (type == " ") return Xwindow::White;
  if (type == "*") return Xwindow::Brown;
  return Xwindow::Black;
}

Graphics::Graphics(Board* b1, Board* b2, std::vector<int> levels, int currPlayer, std::vector<int> scores, std::vector<Block*> &queue1, std::vector<Block*> &queue2, bool blind): window{std::make_unique<Xwindow>(500, 700)},
  b1{b1}, b2{b2}, levels{levels}, currPlayer{currPlayer}, scores{scores}, queue1{queue1}, queue2{queue2}, blind{blind} {
  window->fillRectangle(10, 210, 2, 364, Xwindow::Black);
  window->fillRectangle(10, 210, 224, 2, Xwindow::Black);
  window->fillRectangle(232, 210, 2, 364, Xwindow::Black);
  window->fillRectangle(10, 572, 224, 2, Xwindow::Black);
  // second window
  window->fillRectangle(250, 210, 2, 364, Xwindow::Black);
  window->fillRectangle(250, 210, 224, 2, Xwindow::Black);
  window->fillRectangle(472, 210, 2, 364, Xwindow::Black);
  window->fillRectangle(250, 572, 224, 2, Xwindow::Black);
  window->drawString(15, 593, "Next:");
  window->drawString(255, 593, "Next:");
  for (int i = 2; i <= 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      window->fillRectangle(12 + j * 20, 212 + i * 20, 20, 20, typeToColor(std::string{b1->theBoard.at(i).at(j).getType()}));
      window->fillRectangle(252 + j * 20, 212 + i * 20, 20, 20, typeToColor(std::string{b2->theBoard.at(i).at(j).getType()}));
    }
  }
  for (int i = 0; i < 4; ++i) {
    int x1 = 0;// game->getNextPos().at(i).at(1);
    int y1 = 0;//game->getNextPos().at(i).at(0);
    int x2 = 0;
    int y2 = 0;

      x1 = queue1.at(1)->getPos().at(i).at(1);
      y1 = queue1.at(1)->getPos().at(i).at(0);

      x2 = queue2.at(1)->getPos().at(i).at(1);
      y2 = queue2.at(1)->getPos().at(i).at(0);
    

      window->fillRectangle(15 + 20 * x1, 600 + (y1 - 2) * 20, 20, 20, typeToColor(std::string{queue1.at(1)->getType()}));

      window->fillRectangle(250 + 20 * x2, 600 + (y2 - 2) * 20, 20, 20, typeToColor(std::string{queue2.at(1)->getType()}));
    
    //window->fillRectangle(15 + 20 * x, 600 + (y - 2) * 20, 20, 20, typeToColor(std::string{queue1.at(1)->getType()}/*game->getNextType()*/));
  }
  window->drawString(20, 100, "Player 1 Level:");
  std::ostringstream oss;
  oss << levels[0];
  window->drawString(20, 115, oss.str());
  window->drawString(270, 100, "Player 2 Level:");
  std::ostringstream oss1;
  oss1 << levels[1];
  std::string score1 = std::to_string(scores[0]);
  std::string score2 = std::to_string(scores[1]);
  window->drawString(270, 115, oss1.str());
  window->drawString(20, 150, "Player 1 Score:");
  window->drawString(20, 170, score1);
  window->drawString(270, 150, "Player 2 Score:");
  window->drawString(270, 170, score2);
  window->drawString(200, 50, "hi score:");
  window->drawString(260, 51, "0");
};


void Graphics::updateBoard(std::vector<int> levels, std::vector<int> scores, bool blind) {
  int nextPlayer = (currPlayer+1) % 2;
  // if (blind) window->fillRectangle((nextPlayer ? 252 : 12), 212, 400, 400, Xwindow::Yellow);

  for (int i = 0; i < b1->numRows; ++i) {
    for (int j = 0; j < b1->numCols; ++j) {
      if (i >= 5 && i <= 14 && j >= 2 && j <= 8 && blind) {
        window->drawString((nextPlayer ? 252 : 12) + j * 20, 212 + i * 20, "?");
      }
    //   if (currPlayer == 1) {
        Cell &cell1 = b1->theBoard.at(i).at(j);
        //Cell &cell2 = game->boards[game->curPlayer].board.at(i).at(j);
        Cell &cell3 = b2->theBoard.at(i).at(j);
        //Cell &cell4 = game->boards[!game->curPlayer].board.at(i).at(j);
    //   }
      // if (cell1.getType() != cell2.getType()) {
      //   cell1.updateBlock(cell2.getBlock(), cell2.getType());
        window->fillRectangle((currPlayer ? 252 : 12) + j * 20, 212 + i * 20, 20, 20, typeToColor(std::string{cell1.getType()}));
      // }
      // if (cell3.getType() != cell4.getType()) {
      //   cell3.updateBlock(cell4.getBlock(), cell4.getType());
        window->fillRectangle((currPlayer ? 12 : 252) + j * 20, 212 + i * 20, 20, 20, typeToColor(std::string{cell3.getType()}));
      // }
    }
  }
  window->fillRectangle(0, 600, 200, 40, Xwindow::White);
  window->fillRectangle(240, 600, 200, 40, Xwindow::White);
  for (int i = 0; i < 4; ++i) {
    int x1 = 0;// game->getNextPos().at(i).at(1);
    int y1 = 0;//game->getNextPos().at(i).at(0);
    int x2 = 0;
    int y2 = 0;

      x1 = queue1.at(1)->getPos().at(i).at(1);
      y1 = queue1.at(1)->getPos().at(i).at(0);
      x2 = queue2.at(1)->getPos().at(i).at(1);
      y2 = queue2.at(1)->getPos().at(i).at(0);
    
  
      window->fillRectangle(15 + 20 * x1, 600 + (y1 - 2) * 20, 20, 20, typeToColor(std::string{queue1.at(1)->getType()}/*game->getNextType()*/));

      window->fillRectangle(250 + 20 * x2, 600 + (y2 - 2) * 20, 20, 20, typeToColor(std::string{queue2.at(1)->getType()}/*game->getNextType()*/));
    
    // window->fillRectangle(15 + 20 * x, 600 + (y - 2) * 20, 20, 20, typeToColor(std::string{queue1.at(1)->getType()}/*game->getNextType()*/));
  }
  {
  window->fillRectangle(10, 155, 40, 30, Xwindow::White);
  window->fillRectangle(260, 155, 40, 30, Xwindow::White);
  window->fillRectangle(255, 35, 40, 30, Xwindow::White);
  std::ostringstream oss;
  oss << scores.front();
  window->drawString(20, 170, oss.str());
  std::ostringstream oss1;
  oss1 << scores.back();
  window->drawString(270, 170, oss1.str());
  window->drawString(260, 51, (scores.front() > scores.back() ? oss.str() : oss1.str()));
  }
  std::ostringstream oss;
  oss << levels.front();
  window->fillRectangle(10, 104, 30, 20, Xwindow::White);
  window->fillRectangle(260, 104, 30, 20, Xwindow::White);
  window->drawString(20, 115, oss.str());
  std::ostringstream oss1;
  oss1 << levels.back();
  window->drawString(270, 115, oss1.str());
}
