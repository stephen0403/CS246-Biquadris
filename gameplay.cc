// #include "gameplay.h"
// #include <iostream>

// static bool isFull(const std::vector<char> &row) {
//   for (auto c : row) {
//     if (c == ' ') {
//       return false;
//     }
//   }
//   return true;
// }

// GamePlay::GamePlay(std::string file1, std::string file2, int lvl1, int lvl2, unsigned int seed): boards{Board{}, Board{}},
//   count{1, 1}, playerLevels{lvl1, lvl2}, playerScores{0, 0}, curPlayer{0}, dropped{false}, names{file1, file2} {
//   srand(seed);
//   files.emplace_back(std::ifstream{file1});
//   files.emplace_back(std::ifstream{file2});
//   levels.emplace_back(std::make_unique<Level0>(this));
//   levels.emplace_back(std::make_unique<Level1>(this));
//   levels.emplace_back(std::make_unique<Level2>(this));
//   levels.emplace_back(std::make_unique<Level3>(this));
//   levels.emplace_back(std::make_unique<Level4>(this));
//   queue.emplace_back(levels.at(playerLevels[0])->newBlock());
//   queue.emplace_back(levels.at(playerLevels[1])->newBlock());
//   shift(0, 0, false);
// }

// void GamePlay::notify() {
//   levels[playerLevels[curPlayer]]->effect();
// }

// bool GamePlay::getState() const {
//   return dropped;
// }

// bool GamePlay::getPlayer() const { return curPlayer; }

// void GamePlay::levelUp() {
//   int i = levels.size() - 1;
//   if (playerLevels[curPlayer] < i) {
//     ++playerLevels[curPlayer];
//   }
// }

// void GamePlay::levelDown() {
//   if (playerLevels[curPlayer] > 0) {
//     --playerLevels[curPlayer];
//   }
// }

// void GamePlay::switchPlayer() {
//   if (!clearRows()) {
//     ++count[curPlayer];
//   } else {
//     count[curPlayer] = 1;
//   }
//   dropped = false;
//   queue.erase(queue.begin());
//   queue.emplace_back(levels.at(playerLevels[curPlayer])->newBlock());
//   curPlayer = !curPlayer;
//   if (!shift(0, 0, false)) {
//     throw !curPlayer;
//   }
// }

// bool GamePlay::clearRows() {
//   std::vector<std::vector<char>> newBoard(18, std::vector<char>(11, ' '));
//   int cur_row = 17;
//   bool cleared = false;
//   for (int i = 17; i >= 3; --i) {
//     if (!isFull(boards[curPlayer].board.at(i))) {
//       newBoard.at(cur_row) = boards[curPlayer].board.at(i);
//       --cur_row;
//     } else {
//       cleared = true;
//     }
//   }
//   boards[curPlayer].board = newBoard;
//   return cleared;
// }

// bool GamePlay::shift(int x, int y, bool drop) {
//   auto block = queue.front().get();
//   std::vector<std::vector<int>> &pos = block->pos;
//   for (int i = 0; i < 4; ++i) {
//     boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = ' ';
//   }
//   for (int i = 0; i < 4; ++i) {
//     if (pos[i][0] + y >= boards[0].numRows || pos[i][1] + x < 0 || pos[i][1] + x >= boards[0].numCols ||
//         boards[curPlayer].board.at(pos[i][0] + y).at(pos[i][1] + x) != ' ') {
//       if (y && drop) {
//         dropped = true;
//         for (int i = 0; i < 4; ++i) {
//           if (block->pos[i][0] < 3) {
//             for (int i = 0; i < 4; ++i) {
//               block->pos[i][0] += y;
//               block->pos[i][1] += x;
//               boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = block->getType();
//             }
//             throw !curPlayer;
//           }
//         }
//       }
//       for (int i = 0; i < 4; ++i) {
//         boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = block->getType();
//       }
//       return false;
//     }
//   }
//   block->lowerLeft[0] += y;
//   block->lowerLeft[1] += x;
//   for (int i = 0; i < 4; ++i) {
//     block->pos[i][0] += y;
//     block->pos[i][1] += x;
//     boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = block->getType();
//   }
//   return true;
// }

// void GamePlay::rotateBlock(bool clockwise) {
//   auto block = queue.front().get();
//   std::vector<std::vector<int>> &pos = block->pos;
//   int dest[4][2];
//   if (clockwise) {
//     for (int i = 0; i < 4; ++i) {
//       dest[i][0] = pos[i][1];
//       dest[i][1] = -pos[i][0];
//     }
//   } else {
//     for (int i = 0; i < 4; ++i) {
//       dest[i][0] = -pos[i][1];
//       dest[i][1] = pos[i][0];
//     }
//   }
//   int newLowerLeft[2] = {dest[0][0], dest[0][1]};
//   for (int i = 0; i < 4; ++i) {
//     if (dest[i][0] > newLowerLeft[0]) {
//       newLowerLeft[0] = dest[i][0];
//     }
//     if (dest[i][1] < newLowerLeft[1]) {
//       newLowerLeft[1] = dest[i][1];
//     }
//   }
//   for (int i = 0; i < 4; ++i) {
//     boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = ' ';
//   }
//   for (int i = 0; i < 4; ++i) {
//     dest[i][0] += block->lowerLeft[0] - newLowerLeft[0];
//     dest[i][1] += block->lowerLeft[1] - newLowerLeft[1];
//     if (dest[i][1] >= boards.at(0).numCols || boards[curPlayer].board.at(dest[i][0]).at(dest[i][1]) != ' ') {
//       for (int i = 0; i < 4; ++i) {
//         boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = block->getType();
//       }
//       return;
//     }
//   }
//   for (int i = 0; i < 4; ++i) {
//     block->pos[i][0] = dest[i][0];
//     block->pos[i][1] = dest[i][1];
//     boards[curPlayer].board.at(pos[i][0]).at(pos[i][1]) = block->getType();
//   }
// }

// int GamePlay::getCount() const {
//   return count[curPlayer];
// }

// void GamePlay::putBlock(int col, char type) {
//   for (int i = 3; i < 18; ++i) {
//     if (boards[curPlayer].board.at(i).at(5) != ' ') {
//       if (i > 3) {
//         boards[curPlayer].board.at(i - 1).at(col) = type;
//         return;
//       } else {
//         throw curPlayer;
//       }
//     }
//   }
// }

