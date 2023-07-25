#include "level.h"
#include <iostream>

Level::Level(absBoard *board, bool random): board{board}, random{random} {}

void Level::getFile(std::string) {}

void Level3::getFile(std::string f) {
  name = f;
  file = std::ifstream{f};
}

void Level4::getFile(std::string f) {
  name = f;
  file = std::ifstream{f};
}

Level0::Level0(absBoard *board, std::string name1, std::string name2, bool): Level{board, false} {}

Level1::Level1(absBoard *board, bool): Level{board, true} {}

Level2::Level2(absBoard *board, bool): Level{board, true} {}

Level4::Level4(absBoard *board, bool random): Level{board, random} {}

Level3::Level3(absBoard *board, bool random): Level{board, random} {}

void Level::effect() const {}

void Level::setRandom(bool) {}

void Level3::setRandom(bool r) { random = r; }

void Level4::setRandom(bool r) { random = r; }

std::unique_ptr<Block> Level0::newBlock() {
  char res;
  if (!(files.at(currPlayer) >> res)) {
    files.at(currPlayer) = std::ifstream{names.at(currPlayer)};
    files.at(currPlayer) >> res;
  }
  return blockGen(res);
}

std::unique_ptr<Block> Level1::newBlock() {
  char type[12] = {'I', 'I', 'J', 'J', 'L', 'L', 'T', 'T', 'S', 'Z', 'O', 'O'};
  char res = type[rand() % 12];
  return blockGen(res);
}

std::unique_ptr<Block> Level2::newBlock() {
  char type[7] = {'I', 'J', 'L', 'T', 'S', 'Z', 'O'};
  char res = type[rand() % 7];
  return blockGen(res);
}

std::unique_ptr<Block> Level3::newBlock() {
  if (random) {
    char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
    char res = type[rand() % 9];
  } else {
    char res;
    if (!(file >> res)) {
      file = std::ifstream{name};
      file >> res;
    }
  }
  return blockGen(res);
}

std::unique_ptr<Block> Level4::newBlock() {
  if (random) {
    char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
    char res = type[rand() % 9];
  } else {
    char res;
    if (!(file >> res)) {
      file = std::ifstream{name};
      file >> res;
    }
  }
  return blockGen(res);
}

void Level3::effect() const {
  if (!board->dropped) {
    board->shift(0, 1, false);
  }
}

void Level4::effect() const {
  /*
  if (board->dropped) {
    if (game->getCount() && !(game->getCount() % 5)) {
      game->putBlock(5, '*');
    }
  } else {
  */
    board->shift(0, 1, false);
  //}
}
