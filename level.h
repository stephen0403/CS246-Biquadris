#include "block.h"
#include "absBoard.h"
#include <fstream>
#include <vector>

class absBoard;

class Level {
  protected:
  absBoard *board;
  bool random;
  public:
  Level(absBoard *, bool random);
  virtual std::unique_ptr<Block> newBlock(int currPlayer) = 0;
  virtual void getFile(std::string);
  virtual void setRandom(bool);
};

class Level0: public Level {
  std::vector<std::string> names;
  std::vector<std::ifstream> files;
public:
  Level0(absBoard *board, std::string name1, std::string name2);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level1: public Level {
  public:
  Level1(absBoard *);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level2: public Level {
  public:
  Level2(absBoard *);
  std::unique_ptr<Block> newBlock(int currPlayer) override;
};

class Level3: public Level {
  std::string name;
  std::ifstream file;
  public:
  Level3(absBoard *, bool random, std::string fileName = "sequence.txt");
  std::unique_ptr<Block> newBlock(int currPlayer) override;
  void blind() const;
  void getFile(std::string) override;
  void setRandom(bool) override;
};

class Level4: public Level {
  std::string name;
  std::ifstream file;
  public:
  Level4(absBoard *, bool random, std::string fileName = "sequence.txt");
  std::unique_ptr<Block> newBlock(int currPlayer) override;
  void blind() const;
  void getFile(std::string) override;
  void setRandom(bool) override;
};
