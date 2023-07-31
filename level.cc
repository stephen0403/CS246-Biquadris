#include "level.h"
#include <iostream>

Level::Level(absBoard *board, bool random, unsigned int seed): board{board}, random{random}, seed{seed} {}

void Level::getFile(std::string) {}

void Level3::getFile(std::string f) {
  name = f;
  file = std::ifstream{f};
}

void Level4::getFile(std::string f) {
  name = f;
  file = std::ifstream{f};
}

Level0::Level0(absBoard *board, std::string name1, std::string name2, unsigned int seed): Level{board, false, seed} {
  names.emplace_back(name1);
  names.emplace_back(name2);

  // std::ifstream file1{name1};
  // std::ifstream file2{name2};
  // if (!file1 || !file2) {
  //   std::cerr << "File not found" << std::endl;
  //   exit(1);
  // }
  files.emplace_back(std::ifstream {name1});
  files.emplace_back(std::ifstream {name2});
}

Level1::Level1(absBoard *board, unsigned int seed): Level{board, true, seed} {}

Level2::Level2(absBoard *board, unsigned int seed): Level{board, true, seed} {}

Level3::Level3(absBoard *board, bool random, unsigned int seed, std::string fileName): Level{board, random, seed} {
  if (random) {
    name = fileName;
    file = std::ifstream{fileName};
  }
}

Level4::Level4(absBoard *board, bool random, unsigned int seed, std::string fileName): Level{board, random, seed} {
  if (random) {
    name = fileName;
    file = std::ifstream{fileName};
  }
}

void Level::setRandom(bool) {}

void Level3::setRandom(bool r) { random = r; }

void Level4::setRandom(bool r) { random = r; }

std::unique_ptr<Block> Level0::newBlock(int currPlayer) {
  char res;
  if (!(files.at(currPlayer) >> res)) {
    files.at(currPlayer) = std::ifstream{names.at(currPlayer)};
    files.at(currPlayer) >> res;
  }
  std::cout << "Block for Player " << currPlayer << ": " << res << std::endl;
  return blockGen(res, level);
}

std::unique_ptr<Block> Level1::newBlock(int currPlayer) {
  char type[12] = {'I', 'I', 'J', 'J', 'L', 'L', 'T', 'T', 'S', 'Z', 'O', 'O'};
  srand(seed);
  char res = type[rand() % 12];
  return blockGen(res, level);
}

std::unique_ptr<Block> Level2::newBlock(int currPlayer) {
  char type[7] = {'I', 'J', 'L', 'T', 'S', 'Z', 'O'};
  srand(seed);
  char res = type[rand() % 7];
  return blockGen(res, level);
}

std::unique_ptr<Block> Level3::newBlock(int currPlayer) {
  char res;
  if (random) {
    char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
    srand(seed);
    res = type[rand() % 9];
  } else {
    if (!(file >> res)) {
      file = std::ifstream{name};
      file >> res;
    }
  }
  return blockGen(res, level);
}

std::unique_ptr<Block> Level4::newBlock(int currPlayer) {
  char res;
  if (random) {
    char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
    srand(seed);
    res = type[rand() % 9];
  } else {
    if (!(file >> res)) {
      file = std::ifstream{name};
      file >> res;
    }
  }
  return blockGen(res, level);
}

void Level3::blind() const {
  //if (!board->dropped) {
    //board->shift(0, 1, false);
  //}
  std::cout << "Blinded Board" << std::endl;
}

void Level4::blind() const {
  /*
  if (board->dropped) {
    if (game->getCount() && !(game->getCount() % 5)) {
      game->putBlock(5, '*');
    }
  } else {
  */
    //board->shift(0, 1, false);
  //}
  std::cout << "Blinded Board" << std::endl;
}

void Level4::addStarCount() {
  count++;
}

void Level4::clearStarCount() {
  count = 0;
}

int Level4::getStarCount() {
  return count;
}
