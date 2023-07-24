#include "block.h"
#include <fstream>
#include <vector>

class GamePlay;

class Level {
  protected:
  absBoard *board;
  public:
  Level(absBoard *);
  virtual std::unique_ptr<Block> newBlock() = 0;
  virtual void effect() const;
};

class Level0: public Level {
  std::string name1;
  std::string name2;
  std::ifstream files[2];
  public:
  Level0(absBoard *, std::string, std::string);
  std::unique_ptr<Block> newBlock() override;
};

class Level1: public Level {
  public:
  Level1(absBoard *);
  std::unique_ptr<Block> newBlock() override;
};

class Level2: public Level {
  public:
  Level2(absBoard *);
  std::unique_ptr<Block> newBlock() override;
};

class Level3: public Level {
  public:
  Level3(absBoard *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
};

class Level4: public Level {
  public:
  Level4(absBoard *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
};

