#include "block.h"
#include <fstream>
#include <vector>

class GamePlay;

class Level {
  protected:
  GamePlay *game;
  public:
  Level(GamePlay *);
  virtual std::unique_ptr<Block> newBlock() = 0;
  virtual void effect() const;
};

class Level0: public Level {
  /*
  std::string name1;
  std::string name2;
  std::ifstream file1;
  std::ifstream file2;
  */
  public:
  Level0(GamePlay *);
  std::unique_ptr<Block> newBlock() override;
};

class Level1: public Level {
  public:
  Level1(GamePlay *);
  std::unique_ptr<Block> newBlock() override;
};

class Level2: public Level {
  public:
  Level2(GamePlay *);
  std::unique_ptr<Block> newBlock() override;
};

class Level3: public Level {
  public:
  Level3(GamePlay *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
};

class Level4: public Level {
  public:
  Level4(GamePlay *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
};

