#include <vector>
#include <memory>
#include "block.h"
#include "board.h"
#include "level.h"

class GamePlay {
  std::vector<Board> boards;
  std::vector<std::unique_ptr<Block>> queue;
  std::vector<std::unique_ptr<Level>> levels;
  int count[2];
  int playerLevels[2];
  int playerScores[2];
  bool curPlayer;
  bool dropped;
  friend class TextDisplay;
  // friend class Level;
  public:
  std::vector<std::string> names;
  std::vector<std::ifstream> files;
    GamePlay(std::string, std::string, int lvl1 = 0, int lvl2 = 0, unsigned int seed = 0);
    void notify();
    void levelUp();
    void levelDown();
    void rotateBlock(bool);
    bool shift(int, int, bool drop = false);
    void switchPlayer();
    bool getPlayer() const;
    bool clearRows();
    int getCount() const;
    void putBlock(int, char);
    bool getState() const;
};

