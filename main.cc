#include "board.h"
#include "display.h"
#include <string>
#include <memory>

std::unique_ptr<Block> newBlock(Board *, int);

int main(int argc, char *argv[]) {
  Board boards[2] = {Board{2}, Board{2}};
  Display d{boards, boards + 1};
  bool cur_board = 0;
  std::string cmd;
  std::vector<std::unique_ptr<Block>> queue;
  queue.emplace_back(newBlock(boards, boards[0].getLevel()));
  queue.emplace_back(newBlock(boards + 1, boards[1].getLevel()));
  queue.at(0)->updatePos(0, 0);
  std::cout << d << std::endl << std::endl;
  while (std::cin >> cmd) {
    if (cmd == "d"/*rop"*/) {
      while (queue.at(0)->updatePos(0, 1));
      boards[cur_board].clearRows();
      queue.erase(queue.begin());
      queue.emplace_back(newBlock(boards + cur_board, boards[cur_board].getLevel()));
      cur_board = !cur_board;
      queue.at(0)->updatePos(0, 0);
    } else if (cmd == "c"/*lockwise"*/) {
      queue.at(0)->rotate(1);
    } else if (cmd == "cc"/*ounterclockwise"*/) {
      queue.at(0)->rotate(0);
    } else if (cmd == "r"/*ight"*/) {
      queue.at(0)->updatePos(1, 0);
    } else if (cmd == "l"/*eft"*/) {
      queue.at(0)->updatePos(-1, 0);
    } else if (cmd == "down") {
      if (!queue.at(0)->updatePos(0, 1)) {
        boards[cur_board].clearRows();
        queue.erase(queue.begin());
        queue.emplace_back(newBlock(boards + cur_board, boards[cur_board].getLevel()));
        cur_board = !cur_board;
        queue.at(0)->updatePos(0, 0);
      }
    }
    std::cout << d << std::endl << std::endl;
  }
}


std::unique_ptr<Block> newBlock(Board *board, int lvl) {
  srand((unsigned) time(NULL));
  char res;
  if (lvl == 1) {
    char type[12] = {'I', 'I', 'J', 'J', 'L', 'L', 'T', 'T', 'S', 'Z', 'O', 'O'};
    res = type[rand() % 12];
  } else if (lvl == 2) {
    char type[7] = {'I', 'J', 'L', 'T', 'S', 'Z', 'O'};
    res = type[rand() % 7];
  } else if (lvl == 3) {
    char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
    res = type[rand() % 9];
  }
  if (res == 'I') {
    return std::make_unique<IBlock>(IBlock(board));
  } else if (res == 'J') {
    return std::make_unique<JBlock>(JBlock(board));
  } else if (res == 'L') {
    return std::make_unique<LBlock>(LBlock(board));
  } else if (res == 'T') {
    return std::make_unique<TBlock>(TBlock(board));
  } else if (res == 'S') {
    return std::make_unique<SBlock>(SBlock(board));
  } else if (res == 'Z') {
    return std::make_unique<ZBlock>(ZBlock(board));
  } else { 
    return std::make_unique<OBlock>(OBlock(board));
  }
}
