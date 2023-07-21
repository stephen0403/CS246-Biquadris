#include "level.h"
#include "block.h"

class Level0: public Level {
    string filename;

public:
    Level0(string filename);
    Block *generateBlock() override;
};
