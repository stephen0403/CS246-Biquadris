#include "block.h"
#include <fstream>
#include <vector>

class absBoard;

class Level {
  protected:
  absBoard *board;
  bool random;
  public:
  Level(absBoard board*, bool random);
  virtual std::unique_ptr<Block> newBlock() = 0;
  virtual void effect() const;
  virtual void getFile(std::string);
  virtual void setRandom(bool);
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
  std::string name;
  std::ifstream file;
  public:
  Level3(absBoard *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
  void getFile(std::string) override;
  void setRandom(bool) override;
};

class Level4: public Level {
  std::string name;
  std::ifstream file;
  public:
  Level4(absBoard *);
  std::unique_ptr<Block> newBlock() override;
  void effect() const override;
  void getFile(std::string) override;
  void setRandom(bool) override;
};
