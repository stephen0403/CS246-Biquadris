#ifndef LEVEL0_H
#define LEVEL0_H

#include "level.h"
#include "block.h"

class Level0: public Level {
    string filename;

public:
    Level0(Board *board, string filename);
    Block *generateBlock() override;
};

#endif
