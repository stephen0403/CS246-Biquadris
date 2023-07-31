#include "block.h"
#include "absBoard.h"
#include <fstream>
#include <vector>

class absBoard;

class Level {
protected:
  absBoard *board;
  bool random;
  int level;
  unsigned int seed;
public:
  Level(absBoard *, bool random, unsigned int seed = 0);
  virtual std::unique_ptr<Block> newBlock(int currPlayer) = 0;
  virtual void getFile(std::string);
  virtual void setRandom(bool);
};

class Level0: public Level {
  std::vector<std::string> names;
  std::vector<std::ifstream> files;
  int level = 0;
public:
  Level0(absBoard *board, std::string name1, std::string name2, unsigned int seed);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level1: public Level {
  int level = 1;
public:
  Level1(absBoard *, unsigned int seed);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level2: public Level {
  int level = 2;
public:
  Level2(absBoard *, unsigned int seed);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level3: public Level {
  std::string name;
  std::ifstream file;
  int level = 3;

public:
  Level3(absBoard *, bool random, unsigned int seed, std::string fileName = "sequence.txt");
  std::unique_ptr<Block> newBlock(int currPlayer) override;
  void blind() const;
  void getFile(std::string) override;
  void setRandom(bool) override;
};

class Level4: public Level {
  std::string name;
  std::ifstream file;
  int count = 0;
  int level = 4;

public:
  Level4(absBoard *, bool random, unsigned int seed, std::string fileName = "sequence.txt");
  std::unique_ptr<Block> newBlock(int currPlayer) override;
  void blind() const;
  void getFile(std::string) override;
  void setRandom(bool) override;
  void addStarCount();
  void clearStarCount();
  int getStarCount();
};
