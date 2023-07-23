#include "gameplay.h"
#include <iostream>

Level::Level(GamePlay *game): game{game} {}

Level0::Level0(GamePlay *game): Level{game} {}

Level1::Level1(GamePlay *game): Level{game} {}

Level2::Level2(GamePlay *game): Level{game} {}

Level4::Level4(GamePlay *game): Level{game} {}

Level3::Level3(GamePlay *game): Level{game} {}

void Level::effect() const {}

std::unique_ptr<Block> Level0::newBlock() {
  char res;
  if (!(game->files.at(game->getPlayer()) >> res)) {
    game->files.at(game->getPlayer()) = std::ifstream{game->names.at(game->getPlayer())};
    game->files.at(game->getPlayer()) >> res;
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
  char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
  char res = type[rand() % 9];
  return blockGen(res);
}

std::unique_ptr<Block> Level4::newBlock() {
  char type[9] = {'I', 'J', 'L', 'T', 'S', 'S', 'Z', 'Z', 'O'};
  char res = type[rand() % 9];
  return blockGen(res);
}

void Level3::effect() const {
  if (!game->getState()) {
    game->shift(0, 1, false);
  }
}

void Level4::effect() const {
  if (game->getState()) {
    if (game->getCount() && !(game->getCount() % 5)) {
      game->putBlock(5, '*');
    }
  } else {
    game->shift(0, 1, false);
  }
}

